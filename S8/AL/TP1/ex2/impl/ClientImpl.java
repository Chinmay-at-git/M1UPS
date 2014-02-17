/**
 * 
 */
package impl;

import CS.ClientComponentType;
import services.S_SendMessageToServer;

/**
 * @author 21007631
 *
 */
public class ClientImpl extends ClientComponentType{

	/**
	 * service d'envoie de message au serveur
	 */
	@Override
	protected S_SendMessageToServer make_c_send() {
		return new S_SendMessageToServer(){

			@Override
			public void sendMessage(String message, String clientId) {
				// TODO Auto-generated method stub
				boolean res = requires().s_connect().connectToServer(clientId);
				System.out.println("Connection Status -> " + res);
				System.out.println("Message from " + clientId + " -> " + message);
			}
			
		};
	}

}
