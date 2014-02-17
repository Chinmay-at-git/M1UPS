/**
 * 
 */
package impl;

import CS.ClientComponentType;
import CS.NetworkComponentType;
import CS.ServerComponentType;

/**
 * @author 21007631
 *
 */
public class NetworkImpl extends NetworkComponentType{

	@Override
	protected ClientComponentType make_client() {
		// TODO Auto-generated method stub
		return new ClientImpl();
	}

	@Override
	protected ServerComponentType make_server() {
		// TODO Auto-generated method stub
		return new ServerImpl();
	}

}
