package question3;

import compDefQ3.StartEval;

public class StartEvalImpl extends StartEval {

	@Override
	protected Eval make_evaluate() {
		// TODO Auto-generated method stub
		return new Eval() {

			@Override
			public void start() {
				double res = requires().validateService().evalAndValidate();
				String msg = "La note validée par le processus d'évaluation a donné le résultat de ";
				msg += res;
				requires().printService().requestToPrint(msg);
			}
		};
	}

}
