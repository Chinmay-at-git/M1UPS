package compDefQ4;

import compDefQ2.Print;
import question2.AnnounceInit;
import question4.InitRequest;

@SuppressWarnings("all")
public abstract class PrintIn {
  @SuppressWarnings("all")
  public interface Requires {
    /**
     * This can be called by the implementation to access this required port.
     * 
     */
    public AnnounceInit inDoAnnounce();
    
    /**
     * This can be called by the implementation to access this required port.
     * 
     */
    public InitRequest inInitReq();
  }
  
  
  @SuppressWarnings("all")
  public interface Provides {
    /**
     * This can be called to access the provided port.
     * 
     */
    public AnnounceInit outDoAnnounce();
    
    /**
     * This can be called to access the provided port.
     * 
     */
    public InitRequest outInitReq();
  }
  
  
  @SuppressWarnings("all")
  public interface Component extends PrintIn.Provides {
  }
  
  
  @SuppressWarnings("all")
  public interface Parts {
    /**
     * This can be called by the implementation to access the part and its provided ports.
     * It will be initialized after the required ports are initialized and before the provided ports are initialized.
     * 
     */
    public Print.Component p();
  }
  
  
  @SuppressWarnings("all")
  public static class ComponentImpl implements PrintIn.Component, PrintIn.Parts {
    private final PrintIn.Requires bridge;
    
    private final PrintIn implementation;
    
    public void start() {
      assert this.p != null: "This is a bug.";
      ((Print.ComponentImpl) this.p).start();
      this.implementation.start();
      this.implementation.started = true;
      
    }
    
    protected void initParts() {
      assert this.p == null: "This is a bug.";
      assert this.implem_p == null: "This is a bug.";
      this.implem_p = this.implementation.make_p();
      if (this.implem_p == null) {
      	throw new RuntimeException("make_p() in compDefQ4.PrintIn should not return null.");
      }
      this.p = this.implem_p._newComponent(new BridgeImpl_p(), false);
      
    }
    
    protected void initProvidedPorts() {
      assert this.outDoAnnounce == null: "This is a bug.";
      this.outDoAnnounce = this.implementation.make_outDoAnnounce();
      if (this.outDoAnnounce == null) {
      	throw new RuntimeException("make_outDoAnnounce() in compDefQ4.PrintIn should not return null.");
      }
      assert this.outInitReq == null: "This is a bug.";
      this.outInitReq = this.implementation.make_outInitReq();
      if (this.outInitReq == null) {
      	throw new RuntimeException("make_outInitReq() in compDefQ4.PrintIn should not return null.");
      }
      
    }
    
    public ComponentImpl(final PrintIn implem, final PrintIn.Requires b, final boolean doInits) {
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
    
    private AnnounceInit outDoAnnounce;
    
    public final AnnounceInit outDoAnnounce() {
      return this.outDoAnnounce;
    }
    
    private InitRequest outInitReq;
    
    public final InitRequest outInitReq() {
      return this.outInitReq;
    }
    
    private Print.Component p;
    
    private Print implem_p;
    
    @SuppressWarnings("all")
    private final class BridgeImpl_p implements Print.Requires {
    }
    
    
    public final Print.Component p() {
      return this.p;
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
  
  private PrintIn.ComponentImpl selfComponent;
  
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
  protected PrintIn.Provides provides() {
    assert this.selfComponent != null: "This is a bug.";
    if (!this.init) {
    	throw new RuntimeException("provides() can't be accessed until a component has been created from this implementation, use start() instead of the constructor if provides() is needed to initialise the component.");
    }
    return this.selfComponent;
    
  }
  
  /**
   * This should be overridden by the implementation to define the provided port.
   * This will be called once during the construction of the component to initialize the port.
   * 
   */
  protected abstract AnnounceInit make_outDoAnnounce();
  
  /**
   * This should be overridden by the implementation to define the provided port.
   * This will be called once during the construction of the component to initialize the port.
   * 
   */
  protected abstract InitRequest make_outInitReq();
  
  /**
   * This can be called by the implementation to access the required ports.
   * 
   */
  protected PrintIn.Requires requires() {
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
  protected PrintIn.Parts parts() {
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
  protected abstract Print make_p();
  
  /**
   * Not meant to be used to manually instantiate components (except for testing).
   * 
   */
  public synchronized PrintIn.Component _newComponent(final PrintIn.Requires b, final boolean start) {
    if (this.init) {
    	throw new RuntimeException("This instance of PrintIn has already been used to create a component, use another one.");
    }
    this.init = true;
    PrintIn.ComponentImpl comp = new PrintIn.ComponentImpl(this, b, true);
    if (start) {
    	comp.start();
    }
    return comp;
    
  }
}
