package question4.impl;

import question4.Init;
import compDefQ4.InitProcess;

public class InitProcessImpl extends InitProcess {

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

}
