
/*
    Auteur : Diallo Alpha Oumar Binta
    Numéro étudiant : 21007631
    Groupe 3.2
    Annee scolaire : 2013-2014
    Controle continu numero OIM
*/
// courbe hilbert pseudo code
//enum contient les directions
//Pseudo code


enum {
  UP,
  LEFT,
  DOWN,
  RIGHT,
};

void hilbert(int niveau,int direction=UP)
{
  if (niveau==1) {
    switch (direction) {
    case LEFT:
      move(RIGHT);
      move(DOWN);    
      move(LEFT);
      break;
    case RIGHT:
      move(LEFT);
      move(UP);
      move(RIGHT);
      break;
    case UP:
      move(DOWN);
      move(RIGHT);
      move(UP);
      break;
    case DOWN:
      move(UP);
      move(LEFT);
      move(DOWN);
      break;
    }
  } else {
    switch (direction) {
    case LEFT:
      hilbert_niveau(niveau-1,UP);
      move(RIGHT);
      hilbert_niveau(niveau-1,LEFT);
      move(DOWN);
      hilbert_niveau(niveau-1,LEFT);
      move(LEFT);
      hilbert_niveau(niveau-1,DOWN);
      break;
    case RIGHT:
      hilbert_niveau(niveau-1,DOWN);
      move(LEFT);
      hilbert_niveau(niveau-1,RIGHT);
      move(UP);
      hilbert_niveau(niveau-1,RIGHT);
      move(RIGHT);
      hilbert_niveau(niveau-1,UP);
      break;
    case UP:
      hilbert_niveau(niveau-1,LEFT);
      move(DOWN);
      hilbert_niveau(niveau-1,UP);
      move(RIGHT);
      hilbert_niveau(niveau-1,UP);
      move(UP);
      hilbert_niveau(niveau-1,RIGHT);
      break;
    case DOWN:
      hilbert_niveau(niveau-1,RIGHT);
      move(UP);
      hilbert_niveau(niveau-1,DOWN);
      move(LEFT);
      hilbert_niveau(niveau-1,DOWN);
      move(DOWN);
      hilbert_niveau(niveau-1,LEFT);
      break;
    }
  } 
}