package question1.impl;
import question1.Identifiable;

public class ImplIdentifiable1 extends compDefQ1.Identification {

	@Override
	protected Identifiable make_getID() {
		// TODO Auto-generated method stub
		return new Identifiable() {
			
			@Override
			public String getIdentifiant() {
				String id = "DIALLO/ALPHA_OUMAR_BINTA/5.1";
				return id;
			}
		};
	}

}
