# 𝐒𝟎𝐋𝐈𝐃∆𝐍𝐆𝐋𝐄 - cub3D
cub3D is a 3D graphical project from the 42 curriculum. The goal is to create a basic 3D game engine using raycasting, inspired by early games like Wolfenstein 3D. It uses the MiniLibX graphics library to render a 3D view from a 2D map, allowing the player to move around and interact with the environment.


# Story
# 𝐒𝟎𝐋𝐈𝐃∆𝐍𝐆𝐋𝐄 Palace

## 📖 The Story

In the year 1887, at the heart of the fictional kingdom of Aurelia, the Chess Palace stands tall atop a fog-covered hill. This palace is not merely a royal residence — it is a psychological battlefield, where chess matches are played with living pieces. Each chess piece represents a real person from the royal court — from rebellious pawns to the mysterious queen.

One fateful night, the White Queen vanished, the King was found murdered under mysterious circumstances, and the palace fell into silence. Since then, it has been cursed — haunted by strange entities, and no one who enters ever returns.

Years later, **you awaken**, lost in the dark hallways of the palace. You wear the armor of a black knight — but you don’t remember who you are.  
All you know: **you must reach the Throne Room at the heart of the palace… and uncover the truth**, before you become another piece in a game you never chose to play.

---

## 🕹️ Gameplay

- Each room represents a square on a massive chessboard.
- Some enemies move according to real chess rules (e.g., knights move in L-shapes).
- The game includes mazes, locked doors, cryptic puzzles, and ancient notes.
- You collect “Royal Tokens” to unlock secret parts of the palace.
- The story unfolds through letters, audio echoes, and environment clues.
- No HUD — only sounds, light, and movement guide you.

---

## 👑 Characters (Based on Chess Pieces)

| Piece | Character        | Behavior in the Game                                      |
|-------|------------------|------------------------------------------------------------|
| ♔     | The King         | The murdered ruler — your goal is to discover the truth or avenge him. |
| ♕     | The Queen        | Powerful and unpredictable — sometimes an ally, sometimes not.         |
| ♘     | The Knight       | A rogue warrior — moves in chaotic L-shapes, attacks suddenly.         |
| ♗     | The Bishop       | An ancient priest — gives cryptic puzzles and riddles.                 |
| ♖     | The Rook         | Guardian of the East Gate — won't let you pass unless you're "The King". |
| ♙     | The Pawns        | Emotionless guards — weak but numerous and fast.                       |

---

## 🎨 Atmosphere

- **Victorian Gothic aesthetic**: candles, red carpets, stained glass, shadows.
- **Sound Design**: footsteps behind you, whispered voices, eerie string music.
- **Visuals**: flickering lights, fog-covered corridors, golden-white glows in darkness.
- A surreal sense of time — as if the palace itself is a player in the game.

---

## 🔚 Multiple Endings

Your choices define how the story ends:

- If you help the Queen, you’ll discover she orchestrated the King’s death.
- If you expose the killer, you might be the final piece — and must sacrifice yourself.
- Or... the board resets, and you start again — this time, as the King.

---

## 🚀 Technology

Built using **MiniLibX** and **raycasting techniques**, the game simulates a 3D world with:

- Collision detection
- Sound-based navigation
- Scripted NPC events
- Dynamic lighting and environment changes

# Opening Cutscene (Intro Cinematic)

/*
	[INTRO CUTSCENE]
	Screen fades in from black...
	Soft, distant echo of wind... a ticking clock...
	Text begins to type out slowly.
*/

"In the year 1887... in a land erased from all maps..."

"There stood a palace untouched by war...  
Where battles were waged not with swords — but with strategy."

"A place where kings fell without a cry...  
And silence whispered the loudest threats."

"They called it the SolidAngle —  
A fortress of stone and secrets, where every corridor mirrored a chessboard…  
…and every shadow moved like a piece in play."

/*
	A soft *click* — the sound of a chess piece placed firmly on marble.
	A deep, cold voice echoes from the dark:
*/

"Checkmate."

/*
	Scene fades to silence.
	The screen dims, revealing a grand hallway.
	Heavy breathing. Metallic creaking. You're standing, armored.
*/

"Wh… where am I…?"

"This armor… it feels like a knight's..."

"And beneath my feet… a board? A game?"

/*
	The camera pulls back slowly, revealing a massive chessboard tiled into the palace floor.

	Title appears — cold and regal:
*/

>> “SolidAngle: The Chess Palace” <<

/*
	Game begins.
*/
