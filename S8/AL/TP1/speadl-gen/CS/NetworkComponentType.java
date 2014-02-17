package CS;

import CS.ClientComponentType;
import CS.ServerComponentType;
import services.S_ConnectServer;
import services.S_SendMessageToServer;

@SuppressWarnings("all")
public abstract class NetworkComponentType {
  @SuppressWarnings("all")
  public interface Requires {
  }
  
  
  @SuppressWarnings("all")
  public interface Provides {
    /**
     * This can be called to access the provided port.
     * 
     */
    public S_SendMessageToServer sendService();
  }
  
  
  @SuppressWarnings("all")
  public interface Component extends NetworkComponentType.Provides {
  }
  
  
  @SuppressWarnings("all")
  public interface Parts {
    /**
     * This can be called by the implementation to access the part and its provided ports.
     * It will be initialized after the required ports are initialized and before the provided ports are initialized.
     * 
     */
    public ClientComponentType.Component client();
    
    /**
     * This can be called by the implementation to access the part and its provided ports.
     * It will be initialized after the required ports are initialized and before the provided ports are initialized.
     * 
     */
    public ServerComponentType.Component server();
  }
  
  
  @SuppressWarnings("all")
  public static class ComponentImpl implements NetworkComponentType.Component, NetworkComponentType.Parts {
    private final NetworkComponentType.Requires bridge;
    
    private final NetworkComponentType implementation;
    
    public void start() {
      assert this.client != null: "This is a bug.";
      ((ClientComponentType.ComponentImpl) this.client).start();
      assert this.server != null: "This is a bug.";
      ((ServerComponentType.ComponentImpl) this.server).start();
      this.implementation.start();
      this.implementation.started = true;
      
    }
    
    protected void initParts() {
      assert this.client == null: "This is a bug.";
      assert this.implem_client == null: "This is a bug.";
      this.implem_client = this.implementation.make_client();
      if (this.implem_client == null) {
      	throw new RuntimeException("make_client() in CS.NetworkComponentType should not return null.");
      }
      this.client = this.implem_client._newComponent(new BridgeImpl_client(), false);
      assert this.server == null: "This is a bug.";
      assert this.implem_server == null: "This is a bug.";
      this.implem_server = this.implementation.make_server();
      if (this.implem_server == null) {
      	throw new RuntimeException("make_server() in CS.NetworkComponentType should not return null.");
      }
      this.server = this.implem_server._newComponent(new BridgeImpl_server(), false);
      
    }
    
    protected void initProvidedPorts() {
      
    }
    
    public ComponentImpl(final NetworkComponentType implem, final NetworkComponentType.Requires b, final boolean doInits) {
      this.bridge = b;
      this.implementation = implem;
      
      assert implem.selfComponent == null: "This is a bug.";
      implem.selfComponent = this;
      
      // prevent them to be called twice if we are in
      // a specialized component: only the last of the
      // hierarchy will call them after everything is initialised
      if (doInits) {
      	initParts();
      	initProvidedPorts();
      }
      
    }
    
    public final S_SendMessageToServer sendService() {
      return this.client.c_send();
    }
    
    private ClientComponentType.Component client;
    
    private ClientComponentType implem_client;
    
    @SuppressWarnings("all")
    private final class BridgeImpl_client implements ClientComponentType.Requires {
      public final S_ConnectServer s_connect() {
        return NetworkComponentType.ComponentImpl.this.server.c_connect();
      }
    }
    
    
    public final ClientComponentType.Component client() {
      return this.client;
    }
    
    private ServerComponentType.Component server;
    
    private ServerComponentType implem_server;
    
    @SuppressWarnings("all")
    private final class BridgeImpl_server implements ServerComponentType.Requires {
    }
    
    
    public final ServerComponentType.Component server() {
      return this.server;
    }
  }
  
  
  /**
   * Used to check that two components are not created from the same implementation,
   * that the component has been started to call requires(), provides() and parts()
   * and that the component is not started by hand.
   * 
   */
  private boolean init = false;;
  
  /**
   * Used to check that the component is not started by hand.
   */
  private boolean started = false;;
  
  private NetworkComponentType.ComponentImpl selfComponent;
  
  /**
   * Can be overridden by the implementation.
   * It will be called automatically after the component has been instantiated.
   * 
   */
  protected void start() {
    if (!this.init || this.started) {
    	throw new RuntimeException("start() should not be called by hand: to create a new component, use newComponent().");
    }
    
  }
  
  /**
   * This can be called by the implementation to access the provided ports.
   * 
   */
  protected NetworkComponentType.Provides provides() {
    assert this.selfComponent != null: "This is a bug.";
    if (!this.init) {
    	throw new RuntimeException("provides() can't be accessed until a component has been created from this implementation, use start() instead of the constructor if provides() is needed to initialise the component.");
    }
    return this.selfComponent;
    
  }
  
  /**
   * This can be called by the implementation to access the required ports.
   * 
   */
  protected NetworkComponentType.Requires requires() {
    assert this.selfComponent != null: "This is a bug.";
    if (!this.init) {
    	throw new RuntimeException("requires() can't be accessed until a component has been created from this implementation, use start() instead of the constructor if requires() is needed to initialise the component.");
    }
    return this.selfComponent.bridge;
    
  }
  
  /**
   * This can be called by the implementation to access the parts and their provided ports.
   * 
   */
  protected NetworkComponentType.Parts parts() {
    assert this.selfComponent != null: "This is a bug.";
    if (!this.init) {
    	throw new RuntimeException("parts() can't be accessed until a component has been created from this implementation, use start() instead of the constructor if parts() is needed to initialise the component.");
    }
    return this.selfComponent;
    
  }
  
  /**
   * This should be overridden by the implementation to define how to create this sub-component.
   * This will be called once during the construction of the component to initialize this sub-component.
   * 
   */
  protected abstract ClientComponentType make_client();
  
  /**
   * This should be overridden by the implementation to define how to create this sub-component.
   * This will be called once during the construction of the component to initialize this sub-component.
   * 
   */
  protected abstract ServerComponentType make_server();
  
  /**
   * Not meant to be used to manually instantiate components (except for testing).
   * 
   */
  public synchronized NetworkComponentType.Component _newComponent(final NetworkComponentType.Requires b, final boolean start) {
    if (this.init) {
    	throw new RuntimeException("This instance of NetworkComponentType has already been used to create a component, use another one.");
    }
    this.init = true;
    NetworkComponentType.ComponentImpl comp = new NetworkComponentType.ComponentImpl(this, b, true);
    if (start) {
    	comp.start();
    }
    return comp;
    
  }
  
  /**
   * Use to instantiate a component from this implementation.
   * 
   */
  public NetworkComponentType.Component newComponent() {
    return this._newComponent(new NetworkComponentType.Requires() {}, true);
  }
}
