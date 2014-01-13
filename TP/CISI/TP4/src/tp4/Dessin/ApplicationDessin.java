/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package tp4.Dessin;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

/**
 *
 * @author alphaoumar
 */
public class ApplicationDessin extends javax.swing.JFrame {

    private State currentState;
    /**
     * Creates new form ApplicationDessin
     */
    public ApplicationDessin() {
        initComponents();
           currentState = State.INIT;
           dessin1.addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent me) {}

            @Override
            public void mousePressed(MouseEvent me) {
                switch(currentState){
                    case INIT:
                        currentState = State.INIT;
                        break;
                    case LIGNE:
                        dessin1.setType(new LineDrawable(
                                new Point(me.getPoint()), new Point(me.getPoint())));
                        break;
                    case RECTANGLE:
                        dessin1.setType(new RectangleDrawable(
                                new Point(me.getPoint()), new Point(me.getPoint())));
                        break;
                    case CERCLE:
                       dessin1.setType(new CercleDrawable(
                                new Point(me.getPoint()), new Point(me.getPoint())));
                        break;
                }
            }

            @Override
            public void mouseReleased(MouseEvent me) {
                switch(currentState){
                    case INIT:
                        currentState = State.INIT;
                        break;
                    case LIGNE:
                        dessin1.setP2(new Point(me.getPoint()));
                        dessin1.repaint();
                        break;
                    case RECTANGLE:
                        dessin1.setP2(new Point(me.getPoint()));
                        dessin1.repaint();
                        break;
                    case CERCLE:
                        dessin1.setP2(new Point(me.getPoint()));
                        dessin1.repaint();
                        break;
                }
            }
            @Override
            public void mouseEntered(MouseEvent me) {}

            @Override
            public void mouseExited(MouseEvent me) {}
            });
           
           dessin1.addMouseMotionListener(new MouseMotionListener(){
            @Override
            public void mouseDragged(MouseEvent me) {
                switch(currentState){
                    case INIT:
                        currentState = State.INIT;
                        break;
                    case LIGNE:
                        dessin1.setP2(new Point(me.getPoint()));
                        dessin1.repaint();
                        break;
                    case RECTANGLE:
                        dessin1.setP2(new Point(me.getPoint()));
                        dessin1.repaint();
                        break;
                    case CERCLE:
                        dessin1.setP2(new Point(me.getPoint()));
                        dessin1.repaint();
                        break;
                }
            }
            @Override
            public void mouseMoved(MouseEvent me) { }
               
           });
    }
    
    public void activation(){
        switch(currentState){
            case INIT:
                bCercle.setEnabled(true);
                bRectangle.setEnabled(true);
                bLigne.setEnabled(true);
                break;
            case LIGNE:
                bCercle.setEnabled(true);
                bRectangle.setEnabled(true);
                bLigne.setEnabled(false);
                break;
            case RECTANGLE:
                bCercle.setEnabled(true);
                bRectangle.setEnabled(false);
                bLigne.setEnabled(true);
                break;
            case CERCLE:
                bCercle.setEnabled(false);
                bRectangle.setEnabled(true);
                bLigne.setEnabled(true);
                break;
        }
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        bLigne = new javax.swing.JButton();
        bCercle = new javax.swing.JButton();
        bRectangle = new javax.swing.JButton();
        dessin1 = new tp4.Dessin.Dessin();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Application Dessin");

        bLigne.setText("Ligne");
        bLigne.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bLigneActionPerformed(evt);
            }
        });

        bCercle.setText("Cercle");
        bCercle.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bCercleActionPerformed(evt);
            }
        });

        bRectangle.setText("Rectangle");
        bRectangle.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bRectangleActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout dessin1Layout = new javax.swing.GroupLayout(dessin1);
        dessin1.setLayout(dessin1Layout);
        dessin1Layout.setHorizontalGroup(
            dessin1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 300, Short.MAX_VALUE)
        );
        dessin1Layout.setVerticalGroup(
            dessin1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(dessin1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(bCercle)
                    .addComponent(bLigne)
                    .addComponent(bRectangle))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(dessin1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(bLigne)
                        .addGap(18, 18, 18)
                        .addComponent(bCercle)
                        .addGap(18, 18, 18)
                        .addComponent(bRectangle)
                        .addGap(0, 173, Short.MAX_VALUE)))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void bLigneActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bLigneActionPerformed
        // TODO add your handling code here:
        switch(currentState){
            case INIT:
                currentState = State.LIGNE;
                activation();
                break;
            case LIGNE:
                throw new RuntimeException("ETAT LIGNE INTERDIT");
            case RECTANGLE:
                currentState = State.LIGNE;
                activation();
                break;
            case CERCLE:
                currentState = State.LIGNE;
                activation();
                break;
        }
    }//GEN-LAST:event_bLigneActionPerformed

    private void bCercleActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bCercleActionPerformed
        // TODO add your handling code here:
        switch(currentState){
            case INIT:
                currentState = State.CERCLE;
                activation();
                break;
            case LIGNE:
                currentState = State.CERCLE;
                activation();
                break;
            case RECTANGLE:
                currentState = State.CERCLE;
                activation();
                break;
            case CERCLE:
                 throw new RuntimeException("ETAT CERCLE INTERDIT");
        }
    }//GEN-LAST:event_bCercleActionPerformed

    private void bRectangleActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bRectangleActionPerformed
        // TODO add your handling code here:
        switch(currentState){
            case INIT:
                currentState = State.RECTANGLE;
                activation();
                break;
            case LIGNE:
                currentState = State.RECTANGLE;
                activation();
                break;
            case RECTANGLE:
                throw new RuntimeException("ETAT RECTANGLE INTERDIT");
            case CERCLE:
                currentState = State.RECTANGLE;
                activation();
                break;
        }
    }//GEN-LAST:event_bRectangleActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(ApplicationDessin.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(ApplicationDessin.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(ApplicationDessin.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(ApplicationDessin.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new ApplicationDessin().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton bCercle;
    private javax.swing.JButton bLigne;
    private javax.swing.JButton bRectangle;
    private tp4.Dessin.Dessin dessin1;
    // End of variables declaration//GEN-END:variables
}