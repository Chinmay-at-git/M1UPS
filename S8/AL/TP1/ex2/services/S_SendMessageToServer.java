/*
*Ce service permet d'envoyer des messages au serveur
 * 
 */
package services;

/**
 * @author 21007631
 *
 */
public interface S_SendMessageToServer {
	public void sendMessage(String message, String clientId);

}
