#include "OstreamOverload.h"
#include "Logs/LooseLog.h"
#include "Logs/NewGameLog.h"
#include "Logs/UnidentifiedCommandLog.h"
#include "Logs/UsedCommandLog.h"
#include "Logs/WinLog.h"
#include "Logs/QuitLog.h"
#include "../Commands/Left.h"
#include "../Commands/Right.h"
#include "../Commands/Down.h"
#include "../Commands/Up.h"
#include "../Commands/Quit.h"

std::ostream& operator<<(std::ostream& f, const Log* Called_log){
    if(const WinLog* W = dynamic_cast<const WinLog*>(Called_log)){
        std::map<StatsNames, int> Stats = W->get_stats();
        return f << "Level completed. Statistics[" << "HP: " << Stats[StatsNames::HP] << "; " << "Mana: " << Stats[StatsNames::MANA] << "; " << "Scores: "  << Stats[StatsNames::SCORES] << "; " << "Damage: " << Stats[StatsNames::DAMAGE] << "; " << "Speed: " << Stats[StatsNames::SPEED] << ']' << '\n';
    }
    else if(const LooseLog* L = dynamic_cast<const LooseLog*>(Called_log)){
        return f << "Player lost. Last coordinates: " << '(' << L->get_position().get_x() << ';' << L->get_position().get_y() << ')' << '\n';
    }
    else if(const NewGameLog* NG = dynamic_cast<const NewGameLog*>(Called_log)){
        return f << "New game started. Map size: " << NG->get_field_size_x() << 'x' << NG->get_field_size_y() << "; " << "Position: " << '(' << NG->get_position().get_x() << ';' << NG->get_position().get_y() << ')' << '\n';
    }
    else if(const UnidentifiedCommandLog* UnC = dynamic_cast<const UnidentifiedCommandLog*>(Called_log)){
        return f << "Unknown command. Key: " << static_cast<char>(UnC->get_key()) << '\n';
    }
    else if(const UsedCommandLog* UC = dynamic_cast<const UsedCommandLog*>(Called_log)){
        std::pair<unsigned int, Command*> Used_command = UC->get_command();
        std::string Command_name;
        Command* C = std::get<Command*>(Used_command);
        if(dynamic_cast<Left*>(C)){
            Command_name = "Left";
        }
        else if(dynamic_cast<Right*>(C)){
            Command_name = "Right";
        }
        else if(dynamic_cast<Up*>(C)){
            Command_name = "Up";
        }
        else if(dynamic_cast<Down*>(C)){
            Command_name = "Down";
        }
        else if(dynamic_cast<Quit*>(C)){
            Command_name = "Quit";
        }
        return f << "Command activated. Command name: " << Command_name << "; " << "Key: " << static_cast<char>(std::get<unsigned int>(Used_command)) << ';' << '\n';
    }
    else if(const QuitLog* CL = dynamic_cast<const QuitLog*>(Called_log)){
        return f << "Game closed\n";
    }
    return f << "Unknown log\n";
}