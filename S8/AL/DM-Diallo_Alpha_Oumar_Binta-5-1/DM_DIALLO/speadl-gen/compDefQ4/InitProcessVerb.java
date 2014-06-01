package compDefQ4;

import compDefQ4.InitProcess;
import compDefQ4.PrintIn;
import compDefQ4.PrintOut;
import question2.AnnounceInit;
import question4.Init;
import question4.InitRequest;

@SuppressWarnings("all")
public abstract class InitProcessVerb {
  @SuppressWarnings("all")
  public interface Requires {
    /**
     * This can be called by the implementation to access this required port.
     * 
     */
    public AnnounceInit doAnnounce();
    
    /**
     * This can be called by the implementation to access this required port.
     * 
     */
    public InitRequest initReq();
  }
  
  
  @SuppressWarnings("all")
  public interface Provides {
    /**
     * This can be called to access the provided port.
     * 
     */
    public Init doInit();
  }
  
  
  @SuppressWarnings("all")
  public interface Component extends InitProcessVerb.Provides {
  }
  
  
  @SuppressWarnings("all")
  public interface Parts {
    /**
     * This can be called by the implementation to access the part and its provided ports.
     * It will be initialized after the required ports are initialized and before the provided ports are initialized.
     * 
     */
    public PrintIn.Component pi();
    
    /**
     * This can be called by the implementation to access the part and its provided ports.
     * It will be initialized after the required ports are initialized and before the provided ports are initialized.
     * 
     */
    public PrintOut.Component po();
    
    /**
     * This can be called by the implementation to access the part and its provided ports.
     * It will be initialized after the required ports are initialized and before the provided ports are initialized.
     * 
     */
    public InitProcess.Component pr();
  }
  
  
  @SuppressWarnings("all")
  public static class ComponentImpl implements InitProcessVerb.Component, InitProcessVerb.Parts {
    private final InitProcessVerb.Requires bridge;
    
    private final InitProcessVerb implementation;
    
    public void start() {
      assert this.pi != null: "This is a bug.";
      ((PrintIn.ComponentImpl) this.pi).start();
      assert this.po != null: "This is a bug.";
      ((PrintOut.ComponentImpl) this.po).start();
      assert this.pr != null: "This is a bug.";
      ((InitProcess.ComponentImpl) this.pr).start();
      this.implementation.start();
      this.implementation.started = true;
      
    }
    
    protected void initParts() {
      assert this.pi == null: "This is a bug.";
      assert this.implem_pi == null: "This is a bug.";
      this.implem_pi = this.implementation.make_pi();
      if (this.implem_pi == null) {
      	throw new RuntimeException("make_pi() in compDefQ4.InitProcessVerb should not return null.");
      }
      this.pi = this.implem_pi._newComponent(new BridgeImpl_pi(), false);
      assert this.po == null: "This is a bug.";
      assert this.implem_po == null: "This is a bug.";
      this.implem_po = this.implementation.make_po();
      if (this.implem_po == null) {
      	throw new RuntimeException("make_po() in compDefQ4.InitProcessVerb should not return null.");
      }
      this.po = this.implem_po._newComponent(new BridgeImpl_po(), false);
      assert this.pr == null: "This is a bug.";
      assert this.implem_pr == null: "This is a bug.";
      this.implem_pr = this.implementation.make_pr();
      if (this.implem_pr == null) {
      	throw new RuntimeException("make_pr() in compDefQ4.InitProcessVerb should not return null.");
      }
      this.pr = this.implem_pr._newComponent(new BridgeImpl_pr(), false);
      
    }
    
    protected void initProvidedPorts() {
      assert this.doInit == null: "This is a bug.";
      this.doInit = this.implementation.make_doInit();
      if (this.doInit == null) {
      	throw new RuntimeException("make_doInit() in compDefQ4.InitProcessVerb should not return null.");
      }
      
    }
    
    public ComponentImpl(final InitProcessVerb implem, final InitProcessVerb.Requires b, final boolean doInits) {
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
    
    private Init doInit;
    
    public final Init doInit() {
      return this.doInit;
    }
    
    private PrintIn.Component pi;
    
    private PrintIn implem_pi;
    
    @SuppressWarnings("all")
    private final class BridgeImpl_pi implements PrintIn.Requires {
      public final InitRequest inInitReq() {
        return InitProcessVerb.ComponentImpl.this.bridge.initReq();
      }
      
      public final AnnounceInit inDoAnnounce() {
        return InitProcessVerb.ComponentImpl.this.bridge.doAnnounce();
      }
    }
    
    
    public final PrintIn.Component pi() {
      return this.pi;
    }
    
    private PrintOut.Component po;
    
    private PrintOut implem_po;
    
    @SuppressWarnings("all")
    private final class BridgeImpl_po implements PrintOut.Requires {
      public final Init inDoInit() {
        return InitProcessVerb.ComponentImpl.this.pr.doInit();
      }
    }
    
    
    public final PrintOut.Component po() {
      return this.po;
    }
    
    private InitProcess.Component pr;
    
    private InitProcess implem_pr;
    
    @SuppressWarnings("all")
    private final class BridgeImpl_pr implements InitProcess.Requires {
      public final AnnounceInit doAnnounce() {
        return InitProcessVerb.ComponentImpl.this.pi.outDoAnnounce();
      }
      
      public final InitRequest initReq() {
        return InitProcessVerb.ComponentImpl.this.pi.outInitReq();
      }
    }
    
    
    public final InitProcess.Component pr() {
      return this.pr;
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
  
  private InitProcessVerb.ComponentImpl selfComponent;
  
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
  protected InitProcessVerb.Provides provides() {
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
  protected abstract Init make_doInit();
  
  /**
   * This can be called by the implementation to access the required ports.
   * 
   */
  protected InitProcessVerb.Requires requires() {
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
  protected InitProcessVerb.Parts parts() {
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
  protected abstract PrintIn make_pi();
  
  /**
   * This should be overridden by the implementation to define how to create this sub-component.
   * This will be called once during the construction of the component to initialize this sub-component.
   * 
   */
  protected abstract PrintOut make_po();
  
  /**
   * This should be overridden by the implementation to define how to create this sub-component.
   * This will be called once during the construction of the component to initialize this sub-component.
   * 
   */
  protected abstract InitProcess make_pr();
  
  /**
   * Not meant to be used to manually instantiate components (except for testing).
   * 
   */
  public synchronized InitProcessVerb.Component _newComponent(final InitProcessVerb.Requires b, final boolean start) {
    if (this.init) {
    	throw new RuntimeException("This instance of InitProcessVerb has already been used to create a component, use another one.");
    }
    this.init = true;
    InitProcessVerb.ComponentImpl comp = new InitProcessVerb.ComponentImpl(this, b, true);
    if (start) {
    	comp.start();
    }
    return comp;
    
  }
}
