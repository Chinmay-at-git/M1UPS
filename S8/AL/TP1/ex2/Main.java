import impl.NetworkImpl;
import CS.NetworkComponentType;;

/**
 * 
 */

/**
 * @author 21007631
 *
 */
public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		NetworkComponentType.Component network = (new NetworkImpl()).newComponent();
		
		network.sendService().sendMessage("Hello Server1", "Alpha");

	}

}
