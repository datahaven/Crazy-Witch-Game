/* The Crazy Witch Game
 * by Shair Games
 * Designed by Ari Ron
 *
 * Solution by Adrian Dale 1996
 */

#include <stdio.h>

#define BLUE    1
#define STRIPEY 2
#define PINK    3
#define GREEN   4

/* gbl_iPieces holds the definitions of the game cards,
 * with the colours of the witches starting from the top and
 * going clockwise.
 */
int gbl_aiPieces[9][4] = {
 {BLUE, STRIPEY, PINK, GREEN},
 {PINK, BLUE, STRIPEY, GREEN},
 {PINK, GREEN, STRIPEY, GREEN},
 {STRIPEY, GREEN, PINK, BLUE},
 {STRIPEY, PINK, STRIPEY, GREEN},
 {STRIPEY, BLUE, PINK, BLUE},
 {BLUE, PINK, BLUE, GREEN},
 {PINK, GREEN, STRIPEY, BLUE},
 {GREEN, PINK, BLUE, BLUE}};

/* Macros to access the TOP, RIGHT, BOTTOM and LEFT colours for
 * piece pn, rotation pr.
 */
#define TOP_C(pn, pr)    gbl_aiPieces[pn][pr]
#define RIGHT_C(pn, pr)  gbl_aiPieces[pn][(pr+1)%4]
#define BOTTOM_C(pn, pr) gbl_aiPieces[pn][(pr+2)%4]
#define LEFT_C(pn, pr)   gbl_aiPieces[pn][(pr+3)%4]

/* gbl_aiPlayedSoFar records which piece is placed in a particular
 * position and it's rotation.
 *
 * Position is one of:
 *
 *      0 | 1 | 2
 *     ---+---+---
 *      3 | 4 | 5
 *     ---+---+---
 *      6 | 7 | 8
 *
 * Rotation is the number of 90 degree steps anti-clockwise from the
 * default position.
 *
 * So gbl_aiPlayedSoFar[5][PIECE_NO] will give the number of the
 * piece at position 5.
 * gbl_aiPlayedSoFar[5][PIECE_ROT] will give the rotation of
 * the piece at position 5.
 */
#define PIECE_NO 0
#define PIECE_ROT 1
int gbl_aiPlayedSoFar[9][2];
      
/* FORCE_ROT picks the only possible rotation for piece C, relative
 * to the rotations of A and B, where the pieces are laid out:
 *     | A |
 *   --+ - +
 *   B | C |
 *
 * Usage: C = FORCE_ROT(A, B);
 */
 #define FORCE_ROT(A, B) (((A) == 0 || (A) == 3) ? ((B) <= 1 ? 0 : 3) : ((B) <= 1 ? 1 : 2))
                            
/* Note that these are globals because the parser can't handle the level of
 * indenting needed if we want to keep the whole program in one procedure.
 */                          
int a_piece, a_rot;
int b_piece, b_rot;
int c_piece, c_rot;
int d_piece, d_rot;
int e_piece, e_rot;
int f_piece, f_rot;
int g_piece, g_rot;
int h_piece, h_rot;
int i_piece, i_rot;
void DoLastRow(void);
      
void main()
{

  printf("Crazy Witches puzzle solver by Adrian Dale\n\n");
  
  /* Try every piece in position 0 */
  for (a_piece=0; a_piece<9; a_piece++)
  {
    /* Try each of those pieces in every possible rotation */
    for (a_rot=0; a_rot<4; a_rot++)
    {
      gbl_aiPlayedSoFar[0][PIECE_NO] = a_piece;
      gbl_aiPlayedSoFar[0][PIECE_ROT] = a_rot;

      /* Now try each of the remaining pieces in position 1 */
      for (b_piece=0; b_piece<9; b_piece++)
      {
        /* Don't play a piece we've already played */
        if (a_piece != b_piece)
        {
          /* Try the possible rotations of this piece */
          for (b_rot=0; b_rot<4; b_rot++)
          {
            /* Check that the rotation is valid */
            if ((a_rot == b_rot) ||
                (a_rot == 0 && b_rot == 1) ||
                (a_rot == 1 && b_rot == 0) ||
                (a_rot == 2 && b_rot == 3) ||
                (a_rot == 3 && b_rot == 2))
            {
              gbl_aiPlayedSoFar[1][PIECE_NO] = b_piece;
              gbl_aiPlayedSoFar[1][PIECE_ROT] = b_rot;

              /* See if the colours match */
              if (RIGHT_C(a_piece,a_rot) == LEFT_C(b_piece,b_rot))
              {
              
  /* Try to fit the piece for position 2 */
  /* printf("Matched piece %i, rot %i with piece %i, rot %i\n", a_piece, a_rot, b_piece, b_rot); */
  for (c_piece=0; c_piece<9; c_piece++)
  {
    if (a_piece != c_piece && b_piece != c_piece)
    {
      /* Try the possible rotations of this piece */
      for (c_rot=0; c_rot<4; c_rot++)
      {
      if (b_rot == c_rot ||
          b_rot == 0 && c_rot == 1 ||
          b_rot == 1 && c_rot == 0 ||
          b_rot == 2 && c_rot == 3 ||
          b_rot == 3 && c_rot == 2)
      {
        gbl_aiPlayedSoFar[2][PIECE_NO] = c_piece;
        gbl_aiPlayedSoFar[2][PIECE_ROT] = c_rot;
                        
        /* See if the colours match */
        if (RIGHT_C(b_piece, b_rot) == LEFT_C(c_piece, c_rot))
        {
           /*printf("Match: (%i,%i) (%i,%i) (%i,%i)\n",a_piece+1, a_rot, b_piece+1, b_rot, c_piece+1, c_rot);*/
                          
  /* Try each of the remaining pieces in position 3 */
  for (d_piece=0; d_piece<9; d_piece++)
  {
    if (a_piece != d_piece && b_piece != d_piece && c_piece != d_piece)
    {
      /* Try the possible rotations of this piece */
      for (d_rot=0; d_rot<4; d_rot++)
      {
        if (a_rot == d_rot ||
            a_rot == 0 && d_rot == 3 ||
            a_rot == 3 && d_rot == 0 ||
            a_rot == 2 && d_rot == 1 ||
            a_rot == 1 && d_rot == 2)
        {
          gbl_aiPlayedSoFar[3][PIECE_NO] = d_piece;
          gbl_aiPlayedSoFar[3][PIECE_ROT] = d_rot;
                        
          /* See if the colours match */
          if (BOTTOM_C(a_piece, a_rot) == TOP_C(d_piece, d_rot))
          {  
             /*
             printf("Match: (%i,%i) (%i,%i) (%i,%i) (%i,%i)\n",
             a_piece+1, a_rot,
             b_piece+1, b_rot,
             c_piece+1, c_rot,
             d_piece+1, d_rot);
             */
             
  /* Try each of the remaining pieces in position 4 */
  for (e_piece=0; e_piece<9; e_piece++)
  {
    if (a_piece != e_piece && b_piece != e_piece && c_piece != e_piece && d_piece != e_piece)
    {
      /* Find the only possible rotation of this piece */
      e_rot = FORCE_ROT(b_rot, d_rot);
      
      gbl_aiPlayedSoFar[4][PIECE_NO] = e_piece;
      gbl_aiPlayedSoFar[4][PIECE_ROT] = e_rot;
                        
      /* See if the colours match */
      if (BOTTOM_C(b_piece, b_rot) == TOP_C(e_piece, e_rot) && RIGHT_C(d_piece, d_rot) == LEFT_C(e_piece, e_rot))
      {  
             
        /* printf("Match: (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i,%i)\n",
         a_piece+1, a_rot,
         b_piece+1, b_rot,
         c_piece+1, c_rot,
         d_piece+1, d_rot,
         e_piece+1, e_rot); */
             
   /* Try each of the remaining pieces in position 5 */
  for (f_piece=0; f_piece<9; f_piece++)
  {
    if (a_piece != f_piece && b_piece != f_piece && c_piece != f_piece &&
        d_piece != f_piece && e_piece != f_piece)
    {
      /* Find the only possible rotation of this piece */
      f_rot = FORCE_ROT(c_rot, e_rot);
      
      gbl_aiPlayedSoFar[5][PIECE_NO] = f_piece;
      gbl_aiPlayedSoFar[5][PIECE_ROT] = f_rot;
                        
      /* See if the colours match */
      if (BOTTOM_C(c_piece, c_rot) == TOP_C(f_piece, f_rot) && RIGHT_C(e_piece, e_rot) == LEFT_C(f_piece, f_rot))
      {  
             
         /* printf("Match: (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i, %i)\n",
         a_piece+1, a_rot,
         b_piece+1, b_rot,
         c_piece+1, c_rot,
         d_piece+1, d_rot,
         e_piece+1, e_rot,
         f_piece+1, f_rot); */
         DoLastRow();
      }
    }
  }               
      }
    }
 
  }  
                       
   }
   }
   }
   }
   }                                                    
   }
   }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
 
  
  printf("...and that's the lot...\n");
}

void DoLastRow()
{
         
   /* Try each of the remaining pieces in position 6 */
  for (g_piece=0; g_piece<9; g_piece++)
  {
    if (a_piece != g_piece && b_piece != g_piece && c_piece != g_piece &&
        d_piece != g_piece && e_piece != g_piece && f_piece != g_piece)
    {
      /* Find the possible rotations of this piece */
      for (g_rot=0; g_rot<4; g_rot++)
      {
        if (d_rot == g_rot ||
            d_rot == 0 && g_rot == 3 ||
            d_rot == 3 && g_rot == 0 ||
            d_rot == 2 && g_rot == 1 ||
            d_rot == 1 && g_rot == 2)
        {            
          gbl_aiPlayedSoFar[6][PIECE_NO] = g_piece;
          gbl_aiPlayedSoFar[6][PIECE_ROT] = g_rot;
                        
          /* See if the colours match */
          if (BOTTOM_C(d_piece, d_rot) == TOP_C(g_piece, g_rot))
          {  
             
            /* printf("Match: (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i, %i) (%i, %i)\n",
            a_piece+1, a_rot,
            b_piece+1, b_rot,
            c_piece+1, c_rot,
            d_piece+1, d_rot,
            e_piece+1, e_rot,
            f_piece+1, f_rot,
            g_piece+1, g_rot); */        
   
   
   /* Try each of the remaining pieces in position 7 */
  for (h_piece=0; h_piece<9; h_piece++)
  {
    if (a_piece != h_piece && b_piece != h_piece && c_piece != h_piece &&
        d_piece != h_piece && e_piece != h_piece && f_piece != h_piece &&
        g_piece != h_piece)
    {
      /* Find the only possible rotation of this piece */
      h_rot = FORCE_ROT(e_rot, g_rot);
              
      gbl_aiPlayedSoFar[7][PIECE_NO] = h_piece;
      gbl_aiPlayedSoFar[7][PIECE_ROT] = h_rot;
                        
      /* See if the colours match */
      if (BOTTOM_C(e_piece, e_rot) == TOP_C(h_piece, h_rot) && RIGHT_C(g_piece, g_rot) == LEFT_C(h_piece, h_rot))
      {  
             
        /* printf("Match: (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i, %i) (%i, %i) (%i, %i)\n",
        a_piece+1, a_rot,
        b_piece+1, b_rot,
        c_piece+1, c_rot,
        d_piece+1, d_rot,
        e_piece+1, e_rot,
        f_piece+1, f_rot,
        g_piece+1, g_rot,
        h_piece+1, h_rot); */ 
        
   /* Try the remaining piece in position 8 */
  for (i_piece=0; i_piece<9; i_piece++)
  {
    if (a_piece != i_piece && b_piece != i_piece && c_piece != i_piece &&
        d_piece != i_piece && e_piece != i_piece && f_piece != i_piece &&
        g_piece != i_piece && h_piece != i_piece)
    {
      /* Find the only possible rotation of this piece */
      i_rot = FORCE_ROT(f_rot, h_rot);
              
      gbl_aiPlayedSoFar[8][PIECE_NO] = i_piece;
      gbl_aiPlayedSoFar[8][PIECE_ROT] = i_rot;
                        
      /* See if the colours match */
      if (BOTTOM_C(f_piece, f_rot) == TOP_C(i_piece, i_rot) && RIGHT_C(h_piece, h_rot) == LEFT_C(i_piece, i_rot))
      {  
             
        printf("Match: (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i,%i) (%i,%i)\n",
        a_piece+1, a_rot,
        b_piece+1, b_rot,
        c_piece+1, c_rot,
        d_piece+1, d_rot,
        e_piece+1, e_rot,
        f_piece+1, f_rot,
        g_piece+1, g_rot,
        h_piece+1, h_rot,
        i_piece+1, i_rot);
      }
    }
  }    
      }
    }
  }       
          } 
        }
      }
    }
  }
}