/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package tp3;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.Timer;

/**
 *
 * @author alphaoumar
 */
public class Variante2 extends javax.swing.JFrame {
    //etats possibles
    private enum state{INIT, RED, GREEN, ORANGE, REDORANGE, PANNEON, PANNEOFF}
    //etat courant
    private state currentState;
    //evenement buttonStart, buttonStop, buttonPanne
    private Timer tRed, tGreen, tOrange, tRedOrange, tPanneOn, tPanneOff;
    
    public void redOn(){
        lightOff();
        feu.getRedAmpoule().setAllumer(true);
        feu.repaint();
    }
    public void greenOn(){
        lightOff();
        feu.getGreenAmpoule().setAllumer(true);
        feu.repaint();
    }
    public void orangeOn(){
        lightOff();
        feu.getOrangeAmpoule().setAllumer(true);
        feu.repaint();
    }
    public void turnOff(Ampoule ampoule){
        ampoule.setAllumer(false);
    }
    public void redOrangeOn(){
        lightOff();
        feu.getOrangeAmpoule().setAllumer(true);
        feu.getRedAmpoule().setAllumer(true);
        feu.repaint();
    }
    public void lightOff(){
        turnOff(feu.getRedAmpoule());
        turnOff(feu.getGreenAmpoule());
        turnOff(feu.getOrangeAmpoule());
        feu.repaint();
    }
    
    public void activation(){
        switch(currentState){
            case INIT :
                buttonStart.setEnabled(true);
                buttonStop.setEnabled(false);
                buttonPanne.setEnabled(false);
                tRed.stop();
                tGreen.stop();
                tOrange.stop();
                tRedOrange.stop();
                tPanneOn.stop();
                tPanneOff.stop();
                break;
            case RED:
                buttonStart.setEnabled(false);
                buttonStop.setEnabled(true);
                buttonPanne.setEnabled(true);
                tRed.start();
                tGreen.stop();
                tOrange.stop();
                tRedOrange.stop();
                tPanneOn.stop();
                tPanneOff.stop();
                break;
            case GREEN:
                buttonStart.setEnabled(false);
                buttonStop.setEnabled(true);
                buttonPanne.setEnabled(true);
                tRed.stop();
                tGreen.start();
                tOrange.stop();
                tRedOrange.stop();
                tPanneOn.stop();
                tPanneOff.stop();
                break;
            case ORANGE:
                buttonStart.setEnabled(false);
                buttonStop.setEnabled(true);
                buttonPanne.setEnabled(true);
                tRed.stop();
                tGreen.stop();
                tOrange.start();
                tRedOrange.stop();
                tPanneOn.stop();
                tPanneOff.stop();
                break;
            case REDORANGE:
                buttonStart.setEnabled(false);
                buttonStop.setEnabled(true);
                buttonPanne.setEnabled(true);
                tRed.stop();
                tGreen.stop();
                tOrange.stop();
                tRedOrange.start();
                tPanneOn.stop();
                tPanneOff.stop();
                break;
            case PANNEON:
                buttonStart.setEnabled(true);
                buttonStop.setEnabled(true);
                buttonPanne.setEnabled(false);
                tRed.stop();
                tGreen.stop();
                tOrange.stop();
                tRedOrange.stop();
                tPanneOn.start();
                tPanneOff.stop();
                break;
            case PANNEOFF:
                buttonStart.setEnabled(true);
                buttonStop.setEnabled(true);
                buttonPanne.setEnabled(false);
                tRed.stop();
                tGreen.stop();
                tOrange.stop();
                tRedOrange.stop();
                tPanneOn.stop();
                tPanneOff.start();
                break;
        }
    }
    private void initEvent(){
        //timer feu rouge
        tRed = new Timer(2000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                switch(currentState){
                    case RED :
                        currentState = state.REDORANGE;
                        activation();
                        redOrangeOn();
                        break;
                    default: throw new RuntimeException(currentState.name()
                            + " INTERDIT");
                }
            }
        });
       //timer feu rouge orange
        tRedOrange = new Timer(1000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                switch(currentState){
                    case REDORANGE :
                        currentState = state.GREEN;
                        activation();
                        greenOn();
                        break;
                    default: throw new RuntimeException(currentState.name()
                            + " INTERDIT");
                }
            }
        });
        //timer feu vert
        tGreen = new Timer(3000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                switch(currentState){
                    case GREEN :
                        currentState = state.ORANGE;
                        activation();
                        orangeOn();
                        break;
                    default:
                        throw new RuntimeException(currentState.name()
                                + " INTERDIT");
                }
            }
        });
        //timer feu orange
        tOrange = new Timer(1500, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                switch(currentState){
                    case ORANGE :
                        currentState = state.RED;
                        activation();
                        redOn();
                        break;
                    default:
                        throw new RuntimeException(currentState.name()
                                + " INTERDIT");
                }
            }
        });
        //timer panne on
        tPanneOn = new Timer(1000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                switch(currentState){
                    case PANNEON :
                        currentState = state.PANNEOFF;
                        activation();
                        lightOff();
                        break;
                    default:
                        throw new RuntimeException(currentState.name()
                                + " INTERDIT");
                }
            }
        });
        //timer panne off
        tPanneOff = new Timer(500, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                switch(currentState){
                    case PANNEOFF :
                        currentState = state.PANNEON;
                        activation();
                        orangeOn();
                        break;
                    default:
                        throw new RuntimeException(currentState.name()
                                + " INTERDIT");
                }
            }
        });
        
        //etat initial
        currentState = state.INIT;
        activation();
    }
    /**
     * Creates new form Variante2
     */
    public Variante2() {
        initComponents();
        initEvent();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        buttonStart = new javax.swing.JButton();
        buttonStop = new javax.swing.JButton();
        buttonPanne = new javax.swing.JButton();
        feu = new tp3.Feu();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Britannique");

        buttonStart.setText("Marche");
        buttonStart.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                buttonStartActionPerformed(evt);
            }
        });

        buttonStop.setText("Stop");
        buttonStop.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                buttonStopActionPerformed(evt);
            }
        });

        buttonPanne.setText("Panne");
        buttonPanne.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                buttonPanneActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(29, 29, 29)
                        .addComponent(buttonStart)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(buttonStop)
                        .addGap(18, 18, 18)
                        .addComponent(buttonPanne))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(feu, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addComponent(feu, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 35, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(buttonStart)
                    .addComponent(buttonStop)
                    .addComponent(buttonPanne))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void buttonStartActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_buttonStartActionPerformed
        // TODO add your handling code here:
        switch(currentState){
            case INIT:
            currentState = state.RED;
            activation();
            redOn();
            break;
            case PANNEON:
            currentState = state.RED;
            activation();
            redOn();
            break;
            case PANNEOFF:
            currentState = state.RED;
            activation();
            redOn();
            break;
            default:
            throw new RuntimeException(currentState.name() + " INTERDIT");
        }
    }//GEN-LAST:event_buttonStartActionPerformed

    private void buttonStopActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_buttonStopActionPerformed
        // TODO add your handling code here:
        switch(currentState){
            case INIT:
            throw new RuntimeException(currentState.name() + " INTERDIT");
            default:
            currentState = state.INIT;
            activation();
            lightOff();
            break;
        }
    }//GEN-LAST:event_buttonStopActionPerformed

    private void buttonPanneActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_buttonPanneActionPerformed
        // TODO add your handling code here:
        switch(currentState){
            case INIT:
            throw new RuntimeException(currentState.name() + " INTERDIT");
            case PANNEON:
            throw new RuntimeException(currentState.name() + " INTERDIT");
            case PANNEOFF:
            throw new RuntimeException(currentState.name() + " INTERDIT");
            default:
            currentState = state.PANNEON;
            activation();
            orangeOn();
            break;
        }
    }//GEN-LAST:event_buttonPanneActionPerformed

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
            java.util.logging.Logger.getLogger(Variante2.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Variante2.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Variante2.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Variante2.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new Variante2().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton buttonPanne;
    private javax.swing.JButton buttonStart;
    private javax.swing.JButton buttonStop;
    private tp3.Feu feu;
    // End of variables declaration//GEN-END:variables
}
