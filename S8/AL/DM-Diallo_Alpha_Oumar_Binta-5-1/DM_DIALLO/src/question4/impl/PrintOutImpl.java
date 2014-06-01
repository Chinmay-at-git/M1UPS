package question4.impl;

import question2.PrintingRequest;
import question4.Init;
import compDefQ2.Print;
import compDefQ4.PrintOut;

public class PrintOutImpl extends PrintOut {

	@Override
	protected Init make_outDoInit() {
		// TODO Auto-generated method stub
		return requires().inDoInit();
	}

	@Override
	protected Print make_p() {
		return new Print() {
			
			@Override
			protected PrintingRequest make_pReq() {
				// TODO Auto-generated method stub
				return new PrintingRequest() {
					
					@Override
					public void requestToPrint(String info) {
						// TODO Auto-generated method stub
						String message = "<Out> ==> " + info;
						System.out.println(message);
					}
				};
			}
		};
	}

}
