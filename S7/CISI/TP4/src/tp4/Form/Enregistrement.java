/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package tp4.Form;

/**
 *
 * @author 21007631
 */
public class Enregistrement {
    private String name;
    private int value;

    public Enregistrement() {
    }

    public Enregistrement(String name, int value) {
        this.name = name;
        this.value = value;
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @param name the name to set
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * @return the value
     */
    public int getValue() {
        return value;
    }

    /**
     * @param value the value to set
     */
    public void setValue(int value) {
        this.value = value;
    }

    @Override
    public String toString() {
        return name.toString(); //To change body of generated methods, choose Tools | Templates.
    }
    
}
