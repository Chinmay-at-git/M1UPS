/**
 * 
 */
package impl;
import services.S_ConnectServer;
import CS.ServerComponentType;

/**
 * @author 21007631
 *
 */
public class ServerImpl extends ServerComponentType{

	/**
	 * service de connection d'un client au serveur
	 */
	@Override
	protected S_ConnectServer make_c_connect() {
		// TODO Auto-generated method stub
		return new S_ConnectServer(){

			@Override
			public boolean connectToServer(String clientId) {
				// TODO Auto-generated method stub
				System.out.println("Client " + clientId + " want to connect on the server...");
				return true;
			}
			
		};
	}

}
