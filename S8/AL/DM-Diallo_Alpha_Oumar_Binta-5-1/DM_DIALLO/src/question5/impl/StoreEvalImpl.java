package question5.impl;

import question5.StorableEval;
import compDefQ5.StoreEval;

public class StoreEvalImpl extends StoreEval {

	@Override
	protected StorableEval make_storeService() {
		// TODO Auto-generated method stub
		return new StorableEval() {
			
			@Override
			public void store(String name, double value) {
				System.out.println("[RECORDING] ==> " + name + " - " + value );
			}
		};
	}

}
