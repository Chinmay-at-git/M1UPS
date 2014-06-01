package question1.impl;
import question1.Identifiable;

public class ImplIdentifiable2 extends compDefQ1.Identification {

	@Override
	protected Identifiable make_getID() {
		// TODO Auto-generated method stub
		return new Identifiable() {
			
			@Override
			public String getIdentifiant() {
				String id = "DIALLO 21007631";
				return id;
			}
		};
	}

}
