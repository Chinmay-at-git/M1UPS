/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package tp2;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.Timer;

/**
 *
 * @author alphaoumar
 */
public class EXO2 extends javax.swing.JFrame {

    enum state{INIT, AVANCE, RECULE};
    private int cpt;
    Timer cp1;
    private state currentState;
    /**
     * Creates new form EXO2
     */
    public EXO2() {
        initComponents();
        affichageInit();
    }
    private void affichageInit() {
        currentState = state.INIT;
        zoneAffichage.setText(String.valueOf(cpt));
        cp1 = new Timer(1000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                switch (currentState) {
                    case INIT:
                        throw new RuntimeException("Start INTERDIT");
                    case AVANCE:
                        if(cpt == 3){
                            currentState = state.AVANCE;
                            activation();
                        }else
                            cpt++;
                        affichageCpt();
                    break;
                    case RECULE:
                        if(cpt== -3){
                            currentState = state.RECULE;
                            activation();
                        }else
                            cpt--;
                        affichageCpt();
                    break;
                }
            }
        });
        activation();
    }
    private void affichagePouf(){
       zoneAffichage.setText("Pouf");
    }
    private void affichageCpt(){
        zoneAffichage.setText(String.valueOf(cpt));
    }
    private void activation() {
        switch (currentState) {
            case INIT:
                startButton.setEnabled(true);
                stopButton.setEnabled(false);
                avanceButton.setEnabled(false);
                reculeButton.setEnabled(false);
                cp1.stop();
                break;
            case AVANCE:
                startButton.setEnabled(false);
                avanceButton.setEnabled(false);
                stopButton.setEnabled(true);
                reculeButton.setEnabled(true);
                cp1.start();
                break;
            case RECULE:
                startButton.setEnabled(false);
                avanceButton.setEnabled(true);
                stopButton.setEnabled(true);
                reculeButton.setEnabled(false);
                cp1.start();
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

        zoneAffichage = new javax.swing.JTextField();
        startButton = new javax.swing.JButton();
        stopButton = new javax.swing.JButton();
        avanceButton = new javax.swing.JButton();
        reculeButton = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        zoneAffichage.setEditable(false);
        zoneAffichage.setForeground(new java.awt.Color(255, 0, 0));
        zoneAffichage.setText("jTextField1");

        startButton.setText("Start");
        startButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                startButtonActionPerformed(evt);
            }
        });

        stopButton.setText("Stop");
        stopButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                stopButtonActionPerformed(evt);
            }
        });

        avanceButton.setText("Avance");
        avanceButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                avanceButtonActionPerformed(evt);
            }
        });

        reculeButton.setText("Recule");
        reculeButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                reculeButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(46, 46, 46)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(startButton)
                        .addGap(27, 27, 27)
                        .addComponent(stopButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(avanceButton))
                    .addComponent(zoneAffichage, javax.swing.GroupLayout.PREFERRED_SIZE, 218, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(reculeButton)
                .addContainerGap(65, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(zoneAffichage, javax.swing.GroupLayout.PREFERRED_SIZE, 118, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(33, 33, 33)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(startButton)
                    .addComponent(stopButton)
                    .addComponent(avanceButton)
                    .addComponent(reculeButton))
                .addContainerGap(115, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void startButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_startButtonActionPerformed
        // TODO add your handling code here:
        switch(this.currentState){
            case INIT :
                this.currentState = state.AVANCE;
                activation();
                this.affichageCpt();
            break;
            case AVANCE :
                throw new RuntimeException("INTERDIT");
        }
    }//GEN-LAST:event_startButtonActionPerformed

    private void stopButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_stopButtonActionPerformed
        // TODO add your handling code here:
        switch(this.currentState){
            case INIT :
                throw new RuntimeException("Start INTERDIT");
            case AVANCE :
                this.currentState = state.INIT;
                activation();
                cpt = 0;
                this.affichagePouf();
            case RECULE :
                this.currentState = state.INIT;
                activation();
                cpt = 0;
                this.affichagePouf();
            break;
        }
    }//GEN-LAST:event_stopButtonActionPerformed

    private void avanceButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_avanceButtonActionPerformed
        // TODO add your handling code here:
        switch(this.currentState){
            case INIT :
            throw new RuntimeException("Start INTERDIT");
            case RECULE :
                this.currentState = state.AVANCE;
                activation();
                this.affichageCpt();
            break;
            case AVANCE :
            throw new RuntimeException("AVANCE INTERDIT");
        }
    }//GEN-LAST:event_avanceButtonActionPerformed

    private void reculeButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_reculeButtonActionPerformed
        // TODO add your handling code here:
        switch(this.currentState){
            case INIT :
            throw new RuntimeException("Start INTERDIT");
            case RECULE :
                throw new RuntimeException("RECULE INTERDIT");
            case AVANCE :
                this.currentState = state.RECULE;
                activation();
                this.affichageCpt();
            break;
        }
    }//GEN-LAST:event_reculeButtonActionPerformed

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
            java.util.logging.Logger.getLogger(EXO2.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(EXO2.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(EXO2.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(EXO2.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new EXO2().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton avanceButton;
    private javax.swing.JButton reculeButton;
    private javax.swing.JButton startButton;
    private javax.swing.JButton stopButton;
    private javax.swing.JTextField zoneAffichage;
    // End of variables declaration//GEN-END:variables
}
