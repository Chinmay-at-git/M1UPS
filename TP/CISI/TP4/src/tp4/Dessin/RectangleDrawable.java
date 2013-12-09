/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package tp4.Dessin;

import java.awt.Graphics;
import java.awt.Point;

/**
 *
 * @author 21007631
 */
public class RectangleDrawable extends FormDrawable{

    public RectangleDrawable(Point pos) {
        super(pos);
    }
    public RectangleDrawable(Point pos, Point pos2) {
        super(pos, pos2);
    }

    @Override
    public void draw(Graphics g) {
        g.drawRect(rect.x,rect.y,p2.x,p2.y);
    }
    
}
