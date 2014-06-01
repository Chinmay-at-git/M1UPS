package question2.impl;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import question2.PrintingRequest;
import compDefQ2.Print;

public class PrintImpl2 extends Print {

	@Override
	protected PrintingRequest make_pReq() {
		// TODO Auto-generated method stub
		return new PrintingRequest() {
			
			@Override
			public void requestToPrint(String info) {
				try {
					BufferedWriter write = new BufferedWriter(new FileWriter("Log"));
					write.write(info);
					write.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
				
			}
		};
	}

}
