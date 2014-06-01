package question4.impl;

import question4.Init;
import compDefQ4.InitProcess;
import compDefQ4.InitProcessVerb;
import compDefQ4.PrintIn;
import compDefQ4.PrintOut;

public class InitProcessVerbImpl extends InitProcessVerb {

	@Override
	protected Init make_doInit() {
		// TODO Auto-generated method stub
		return new Init() {
			
			@Override
			public void startInitStep() {
				String id = requires().initReq().getIdForNewEval();
				requires().doAnnounce().startProcessFor(id);
			}
		};
	}

	@Override
	protected PrintIn make_pi() {
		// TODO Auto-generated method stub
		return new PrintInImpl();
	}

	@Override
	protected PrintOut make_po() {
		// TODO Auto-generated method stub
		return new PrintOutImpl();
	}

	@Override
	protected InitProcess make_pr() {
		// TODO Auto-generated method stub
		return new InitProcessImpl();
	}

}
