package question4.impl;

import question2.AnnounceInit;
import question2.PrintingRequest;
import question4.InitRequest;
import compDefQ2.Print;
import compDefQ4.PrintIn;

public class PrintInImpl extends PrintIn {

	@Override
	protected AnnounceInit make_outDoAnnounce() {
		// TODO Auto-generated method stub
		return requires().inDoAnnounce();
	}

	@Override
	protected InitRequest make_outInitReq() {
		// TODO Auto-generated method stub
		return requires().inInitReq();
	}

	@Override
	protected Print make_p() {
		// TODO Auto-generated method stub
		return new Print() {
			
			@Override
			protected PrintingRequest make_pReq() {
				// TODO Auto-generated method stub
				return new PrintingRequest() {
					
					@Override
					public void requestToPrint(String info) {
						System.out.println("<IN> ==> " + info);						
					}
				};
			}
		};
	}

}
