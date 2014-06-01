package question5.impl;

import question5.ComputableEval;
import compDefQ5.ComputeEval;

public class ComputeEvalImpl extends ComputeEval {

	@Override
	protected ComputableEval make_evalService() {
		// TODO Auto-generated method stub
		return new ComputableEval() {
			
			@Override
			public double eval(String subject) {
				return 15;
			}
		};
	}

}
