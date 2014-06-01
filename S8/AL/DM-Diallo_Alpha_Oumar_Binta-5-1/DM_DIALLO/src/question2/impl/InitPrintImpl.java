package question2.impl;

import question2.AnnounceInit;
import compClientDefQ2.InitPrint;

public class InitPrintImpl extends InitPrint {

	@Override
	protected AnnounceInit make_announceService() {
		// TODO Auto-generated method stub
		return new AnnounceInit() {
			
			@Override
			public void startProcessFor(String subject) {
				requires().printingService().requestToPrint(subject);
			}
		};
	}

}
