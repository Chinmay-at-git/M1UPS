package compDefQ3;

import compDefQ2.Print;
import compDefQ3.StartEval;
import compDefQ3.ValidateComp;
import question2.PrintingRequest;
import question3.Eval;
import question3.EvalRequest;
import question3.ValidateRequest;

@SuppressWarnings("all")
public abstract class CompositeQ3 {
  @SuppressWarnings("all")
  public interface Requires {
    /**
     * This can be called by the implementation to access this required port.
     * 
     */
    public EvalRequest evalValid();
  }
  
  
  @SuppressWarnings("all")
  public interface Provides {
    /**
     * This can be called to access the provided port.
     * 
     */
    public Eval eval();
  }
  
  
  @SuppressWarnings("all")
  public interface Component extends CompositeQ3.Provides {
  }
  
  
  @SuppressWarnings("all")
  public interface Parts {
    /**
     * This can be called by the implementation to access the part and its provided ports.
     * It will be initialized after the required ports are initialized and before the provided ports are initialized.
     * 
     */
    public StartEval.Component se();
    
    /**
     * This can be called by the implementation to access the part and its provided ports.
     * It will be initialized after the required ports are initialized and before the provided ports are initialized.
     * 
     */
    public Print.Component p();
    
    /**
     * This can be called by the implementation to access the part and its provided ports.
     * It will be initialized after the required ports are initialized and before the provided ports are initialized.
     * 
     */
    public ValidateComp.Component v();
  }
  
  
  @SuppressWarnings("all")
  public static class ComponentImpl implements CompositeQ3.Component, CompositeQ3.Parts {
    private final CompositeQ3.Requires bridge;
    
    private final CompositeQ3 implementation;
    
    public void start() {
      assert this.se != null: "This is a bug.";
      ((StartEval.ComponentImpl) this.se).start();
      assert this.p != null: "This is a bug.";
      ((Print.ComponentImpl) this.p).start();
      assert this.v != null: "This is a bug.";
      ((ValidateComp.ComponentImpl) this.v).start();
      this.implementation.start();
      this.implementation.started = true;
      
    }
    
    protected void initParts() {
      assert this.se == null: "This is a bug.";
      assert this.implem_se == null: "This is a bug.";
      this.implem_se = this.implementation.make_se();
      if (this.implem_se == null) {
      	throw new RuntimeException("make_se() in compDefQ3.CompositeQ3 should not return null.");
      }
      this.se = this.implem_se._newComponent(new BridgeImpl_se(), false);
      assert this.p == null: "This is a bug.";
      assert this.implem_p == null: "This is a bug.";
      this.implem_p = this.implementation.make_p();
      if (this.implem_p == null) {
      	throw new RuntimeException("make_p() in compDefQ3.CompositeQ3 should not return null.");
      }
      this.p = this.implem_p._newComponent(new BridgeImpl_p(), false);
      assert this.v == null: "This is a bug.";
      assert this.implem_v == null: "This is a bug.";
      this.implem_v = this.implementation.make_v();
      if (this.implem_v == null) {
      	throw new RuntimeException("make_v() in compDefQ3.CompositeQ3 should not return null.");
      }
      this.v = this.implem_v._newComponent(new BridgeImpl_v(), false);
      
    }
    
    protected void initProvidedPorts() {
      assert this.eval == null: "This is a bug.";
      this.eval = this.implementation.make_eval();
      if (this.eval == null) {
      	throw new RuntimeException("make_eval() in compDefQ3.CompositeQ3 should not return null.");
      }
      
    }
    
    public ComponentImpl(final CompositeQ3 implem, final CompositeQ3.Requires b, final boolean doInits) {
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
    
    private Eval eval;
    
    public final Eval eval() {
      return this.eval;
    }
    
    private StartEval.Component se;
    
    private StartEval implem_se;
    
    @SuppressWarnings("all")
    private final class BridgeImpl_se implements StartEval.Requires {
      public final PrintingRequest printService() {
        return CompositeQ3.ComponentImpl.this.p.pReq();
      }
      
      public final ValidateRequest validateService() {
        return CompositeQ3.ComponentImpl.this.v.validReq();
      }
    }
    
    
    public final StartEval.Component se() {
      return this.se;
    }
    
    private Print.Component p;
    
    private Print implem_p;
    
    @SuppressWarnings("all")
    private final class BridgeImpl_p implements Print.Requires {
    }
    
    
    public final Print.Component p() {
      return this.p;
    }
    
    private ValidateComp.Component v;
    
    private ValidateComp implem_v;
    
    @SuppressWarnings("all")
    private final class BridgeImpl_v implements ValidateComp.Requires {
      public final EvalRequest evReq() {
        return CompositeQ3.ComponentImpl.this.bridge.evalValid();
      }
    }
    
    
    public final ValidateComp.Component v() {
      return this.v;
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
  
  private CompositeQ3.ComponentImpl selfComponent;
  
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
  protected CompositeQ3.Provides provides() {
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
  protected abstract Eval make_eval();
  
  /**
   * This can be called by the implementation to access the required ports.
   * 
   */
  protected CompositeQ3.Requires requires() {
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
  protected CompositeQ3.Parts parts() {
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
  protected abstract StartEval make_se();
  
  /**
   * This should be overridden by the implementation to define how to create this sub-component.
   * This will be called once during the construction of the component to initialize this sub-component.
   * 
   */
  protected abstract Print make_p();
  
  /**
   * This should be overridden by the implementation to define how to create this sub-component.
   * This will be called once during the construction of the component to initialize this sub-component.
   * 
   */
  protected abstract ValidateComp make_v();
  
  /**
   * Not meant to be used to manually instantiate components (except for testing).
   * 
   */
  public synchronized CompositeQ3.Component _newComponent(final CompositeQ3.Requires b, final boolean start) {
    if (this.init) {
    	throw new RuntimeException("This instance of CompositeQ3 has already been used to create a component, use another one.");
    }
    this.init = true;
    CompositeQ3.ComponentImpl comp = new CompositeQ3.ComponentImpl(this, b, true);
    if (start) {
    	comp.start();
    }
    return comp;
    
  }
}
