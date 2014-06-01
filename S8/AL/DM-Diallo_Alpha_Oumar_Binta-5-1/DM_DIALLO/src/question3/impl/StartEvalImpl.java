package question3.impl;

import question3.Eval;
import compDefQ3.StartEval;

public class StartEvalImpl extends StartEval {

	@Override
	protected Eval make_evaluate() {
		// TODO Auto-generated method stub
		return new Eval() {

			@Override
			public void start() {
				double res = requires().validateService().evalAndValidate();
				String message = "La note validée par le processus d'évaluation donne le résultat ==>";
				message += res;
				requires().printService().requestToPrint(message);
			}
		};
	}

}
