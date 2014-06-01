package question3.impl;

import question2.impl.PrintImpl;
import question3.Eval;
import compDefQ2.Print;
import compDefQ3.CompositeQ3;
import compDefQ3.StartEval;
import compDefQ3.ValidateComp;

public class CompositeQ3Impl extends CompositeQ3 {

	@Override
	protected Eval make_eval() {
		// TODO Auto-generated method stub
		return new Eval() {
			
			@Override
			public void start() {
				// TODO Auto-generated method stub
				
			}
		};
	}

	@Override
	protected StartEval make_se() {
		// TODO Auto-generated method stub
		return new StartEvalImpl();
	}

	@Override
	protected Print make_p() {
		// TODO Auto-generated method stub
		return new PrintImpl();
	}

	@Override
	protected ValidateComp make_v() {
		// TODO Auto-generated method stub
		return new ValidateImpl();
	}

}
