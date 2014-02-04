/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package tp4.Dessin;

import java.awt.Point;
import java.awt.Rectangle;
/**
 *
 * @author 21007631
 */
public abstract class FormDrawable implements IDrawable{
    protected Rectangle rect ;
    protected Point p2;
    
    public FormDrawable(Point pos){
        this.rect = new Rectangle(pos);
    }
    
    public FormDrawable(Point pos, Point p){
        this.rect = new Rectangle(pos);
        p2 = p;
    }
    public Rectangle getRectangle(){
        return (Rectangle) rect;
    }

    /**
     * @return the p2
     */
    public Point getP2() {
        return p2;
    }

    /**
     * @param p2 the p2 to set
     */
    public void setP2(Point p2) {
        this.p2 = p2;
    }
}
