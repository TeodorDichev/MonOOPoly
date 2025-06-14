#MONOOPOLY GAME

🎲 Welcome to Monoopoly – a console-based C++ remake of the classic property trading game, built with strategy, luck, and a bit of C++ magic.

🔥 Features:
- Turn-based gameplay for 2–6 players
- Field upgrades, mortgages, and dynamic trading
- Automatic game saving using binary files
- Full game data customization via editable text files (Fields.txt, Cards.txt)
- Built with **Command**, **Visitor**, and **Factory** design patterns

--------------------------
   GAMEPLAY COMMANDS
--------------------------

# Before the Game
- `start_new_game <2–6>`    Start a new match
- `load_game`               Resume your last saved game
- `help`                    List all available commands

# During the Game
- `roll`                    Roll dice and move
- `sell_field <id>`         Sell your property
- `check_field <id>`        View field info
- `upgrade_mortgage <id>`   Upgrade with cottage/castle
- `resign`                  Forfeit the match
- `save_game`               Save your progress

# Trading
- `make_trade <player> <field> <amount>` Send trade offers
- `accept_trade <trade_id>`               Accept offers
- `view_trades`                           View trade history

💡 Notes:
- Own all properties of a color to unlock cottages; castles come after.
- Mortgaged properties are lost when sold.
- Prison skips a turn; you can buy freedom.
- Can't pay a debt? Your cheapest field is sold automatically.
- Edit `Cards.txt` and `Fields.txt` to customize your own Monoopoly — just don't break the format!

👑 May the shrewdest player win!

