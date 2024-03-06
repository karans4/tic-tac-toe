#include <raylib.h>

#define WINDOWSIZE 1000
#define LEFT_CLICK 0

typedef enum Square {
  EMPTY,
  X,
  O,
} Square;

typedef enum Player {
  PLAYER_X,
  PLAYER_O
} Player;

int main() {
  InitWindow(WINDOWSIZE, WINDOWSIZE, "Tic Tac Toe");

  /* A goto was easier than writing functions.
     I didn't want to use global variables and passing
     all the arguments seemed like such a hassle.
     I wrote this whole thing in an hour on a lazy afternoon
     Don't judge
  */
  
 begining:
  /* Initialize the board */
  Player turn = PLAYER_O;
  Square winner = EMPTY;
  Square board[3][3] = {{EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY}};

  ShowCursor();
  SetTargetFPS(60);
  
  while (!WindowShouldClose() && winner == EMPTY) {
    
    BeginDrawing();
    ClearBackground(BLACK);

    /* Get the user input and deal with Game Logic */
    
    {
      Vector2 mouse_position = GetMousePosition();
      Vector2 square_selected;
      
      if(turn == PLAYER_O) {
	DrawText("Player O! Make your move! Click on a square!",
		 WINDOWSIZE/5/2,
		 WINDOWSIZE/5/2,
		 30, BLUE);
      }
      else {
	DrawText("Player X! Make your move! Click on a square!",
		 WINDOWSIZE/5/2,
		 WINDOWSIZE/5/2,
		 30, RED);
      }

      square_selected.y = (mouse_position.y - WINDOWSIZE/5)/ (WINDOWSIZE/5);
      square_selected.x = (mouse_position.x - WINDOWSIZE/5)/ (WINDOWSIZE/5);

      /* It's all just one big if statement but it's split up for readability */
      
      
      if(IsMouseButtonPressed(LEFT_CLICK)) {
	
	/* If mouse is in bounds */
	if (square_selected.x < 3 && square_selected.x >= 0 ) {
	  if (square_selected.y < 3 && square_selected.y >= 0) {

	    /* if square_selected is empty */
	    if (board[(int) square_selected.y][(int) square_selected.x] == EMPTY) {
	      board[(int) square_selected.y][(int) square_selected.x] = (turn == PLAYER_O ? O : X);
	      turn = (turn == PLAYER_O ? PLAYER_X : PLAYER_O);
	    }
	  }
	}

      }
            
    }

    /* Draw the board to the screen */
    
    /* Draw horizonal lines */

    DrawLine(WINDOWSIZE / 5, WINDOWSIZE/5 * 2,
	     WINDOWSIZE/5 * 4, WINDOWSIZE/5 * 2,
	     WHITE);
    
    DrawLine(WINDOWSIZE / 5, WINDOWSIZE/5 * 3,
	     WINDOWSIZE/5 * 4,WINDOWSIZE/5 * 3,
	     WHITE);

    /* Board looks like this
         
      -----------
         
      -----------
         
    */
    
    /* Draw Vertical lines */
    DrawLine(WINDOWSIZE/5 * 2, WINDOWSIZE/5,
	     WINDOWSIZE/5 * 2,WINDOWSIZE/5 *4,
	     WHITE);
    DrawLine(WINDOWSIZE/5 * 3, WINDOWSIZE/5,
	     WINDOWSIZE/5 * 3,WINDOWSIZE/5 *4,
	     WHITE);

    /* Board looks like this
         |   |  
      -----------
         |   |  
      -----------
         |   |  
    */

    
    /* Draw the Os and the Xs on the board */
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
	if (board[i][j] == EMPTY) {
	  /* Draw Nothing */
	  continue;
	}
	else {
	  if (board[i][j] == X) {
	    /* Draw an X as two lines from corner to corner diagonally*/
	    Vector2 slash_line_start = {WINDOWSIZE/5 + WINDOWSIZE/5 * j,
					WINDOWSIZE/5 + WINDOWSIZE/5 * i},
	      slash_line_stop = {WINDOWSIZE/5 + WINDOWSIZE/5 * (j + 1),
				 WINDOWSIZE/5 + WINDOWSIZE/5 * (i + 1)},
	    
	      backslash_line_start = {WINDOWSIZE/5 + WINDOWSIZE/5 * (j + 1),
				      WINDOWSIZE/5 + WINDOWSIZE/5 * i},
	      backslash_line_stop = {WINDOWSIZE/5 + WINDOWSIZE/5 * j,
				     WINDOWSIZE/5 + WINDOWSIZE/5 * (i + 1)};
	    
	    DrawLineEx(slash_line_start, slash_line_stop, 3, RED);
	    DrawLineEx(backslash_line_start, backslash_line_stop, 3, RED);
	  }
	  else {
	    DrawCircle(WINDOWSIZE/5/2*3 + WINDOWSIZE/5 * j,
		       WINDOWSIZE/5/2*3 + WINDOWSIZE/5 * i,
		       WINDOWSIZE/5/2, BLUE);
	  }
	}
      }
    }


    /* Board looks like this
       X |   | O
      -----------
         | O |  
      -----------
       X |   | 
    */

    
    /* See if someone won */
    
    for (int i = 0; i < 3; i++) {
      /* Check if a row is all the same */
      if (board[i][0] != EMPTY &&
	  board[i][0] == board[i][1] &&
	  board[i][0] == board[i][2]) {
	
	winner = board[i][0];
	EndDrawing();
	goto endscreen;
      }
    }

    
    for (int j = 0; j < 3; j++) {
      /* Check if a column is all the same */
      if (board[0][j] != EMPTY &&
	  board[0][j] == board[1][j] &&
	  board[0][j] == board[2][j]) {
	
	winner = board[0][j];
	EndDrawing();
	goto endscreen;
      }
    }

    /* Check this Diagonal --> \ <-- */
    if (board[0][0] != EMPTY &&
	board[0][0] == board[1][1] &&
	board[0][0] == board[2][2]) {
      winner = board[0][0];
      EndDrawing();
      goto endscreen;
    }
    
    
    /* Check this Diagonal --> / <-- */
    if (board[0][2] != EMPTY &&
	board[0][2] == board[1][1] &&
	board[0][2] == board[2][0]) {
      
      winner = board[0][2];
      EndDrawing();
      goto endscreen;
    }
    
    /* See if board is full, but no one won. */
    {
      for (int i = 0; i < 3; i++) {
	  for (int j = 0; j < 3; j++) {
	    if (board[i][j] == EMPTY) {
	      /* If an empty square was found, continue as normal */
	      goto keepgoing;
	    }
	  }
      }
      
      winner = EMPTY;
      goto endscreen;
    }
     	  
	
	
    
  keepgoing:	
    EndDrawing();
  }
  
  return 0;

  endscreen:
  /* This stuff is only drawn once instead of every frame */
  /* We just don't clear the screen in between frames */
  BeginDrawing();
  /* Gray out screen*/
  DrawRectangle(0, 0,
		WINDOWSIZE, WINDOWSIZE,
		(Color){0,0,0,200});
  
  switch (winner) {
  case O:
    DrawText("Player O Wins!", WINDOWSIZE/5, WINDOWSIZE/5*2, 80, BLUE);
    break;
  case X:
    DrawText("Player X Wins!", WINDOWSIZE/5, WINDOWSIZE/5*2, 80, RED);
    break;
  default:
    DrawText("No one wins.", WINDOWSIZE/5, WINDOWSIZE/5*2, 80, WHITE);
    break;
  }
  
  DrawText("Click anywhere to play again.", WINDOWSIZE/5, WINDOWSIZE/5*3, 30, WHITE);
    
  EndDrawing();

  while (!WindowShouldClose()) {

    /* Required for getting mouse button click state */
    BeginDrawing();
    EndDrawing();
    
    if (IsMouseButtonPressed(LEFT_CLICK)) {
      // reset board
      goto begining;
    }
  }
  return 0;
}
