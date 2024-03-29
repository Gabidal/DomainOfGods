/*
    GGUI Lightweight Terminal UI
    Version 0.1.1
    HAVE FUN!
*/

#pragma once
#ifndef _GGUI_H_
#define _GGUI_H_

//This header is used with the GGUI.lib.
#undef min
#undef max

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <chrono>
#include <atomic>
#include <unordered_map>
#include <thread>
#include <iostream>
#include <fstream>


namespace GGUI{
    //GGUI uses the ANSI escape code
    //https://en.wikipedia.org/wiki/ANSI_escape_code

    namespace SYMBOLS{
        inline std::string TOP_LEFT_CORNER = "┌";//"\e(0\x6c\e(B";
        inline std::string BOTTOM_LEFT_CORNER = "└";//"\e(0\x6d\e(B";
        inline std::string TOP_RIGHT_CORNER = "┐";//"\e(0\x6b\e(B";
        inline std::string BOTTOM_RIGHT_CORNER = "┘";//"\e(0\x6a\e(B";
        inline std::string VERTICAL_LINE = "│";//"\e(0\x78\e(B";
        inline std::string HORIZONTAL_LINE = "─";//"\e(0\x71\e(B";
        inline std::string VERTICAL_RIGHT_CONNECTOR = "├";//"\e(0\x74\e(B";
        inline std::string VERTICAL_LEFT_CONNECTOR = "┤";//"\e(0\x75\e(B";
        inline std::string HORIZONTAL_BOTTOM_CONNECTOR = "┬";//"\e(0\x76\e(B";
        inline std::string HORIZONTAL_TOP_CONNECTOR = "┴";//"\e(0\x77\e(B";
        inline std::string CROSS_CONNECTOR = "┼";//"\e(0\x6e\e(B";

        inline std::string CENTERED_HORIZONTAL_LINE = "━";//"\e(0\x71\e(B";
        inline std::string FULL_BLOCK = "█";//"\e(0\xdb\e(B";

        inline unsigned int CONNECTS_UP = 1 << 0;
        inline unsigned int CONNECTS_DOWN = 1 << 1;
        inline unsigned int CONNECTS_LEFT = 1 << 2;
        inline unsigned int CONNECTS_RIGHT = 1 << 3;

        inline std::string RADIOBUTTON_OFF = "○";
        inline std::string RADIOBUTTON_ON = "◉";

        inline std::string EMPTY_CHECK_BOX = "☐";
        inline std::string CHECKED_CHECK_BOX = "☒";

        inline std::map<unsigned int, std::string> Border_Identifiers = {

            {CONNECTS_DOWN | CONNECTS_RIGHT, TOP_LEFT_CORNER},
            {CONNECTS_DOWN | CONNECTS_LEFT, TOP_RIGHT_CORNER},
            {CONNECTS_UP | CONNECTS_RIGHT, BOTTOM_LEFT_CORNER},
            {CONNECTS_UP | CONNECTS_LEFT, BOTTOM_RIGHT_CORNER},

            {CONNECTS_DOWN | CONNECTS_UP, VERTICAL_LINE},

            {CONNECTS_LEFT | CONNECTS_RIGHT, HORIZONTAL_LINE},

            {CONNECTS_DOWN | CONNECTS_UP | CONNECTS_RIGHT, VERTICAL_RIGHT_CONNECTOR},
            {CONNECTS_DOWN | CONNECTS_UP | CONNECTS_LEFT, VERTICAL_LEFT_CONNECTOR},

            {CONNECTS_LEFT | CONNECTS_RIGHT | CONNECTS_DOWN, HORIZONTAL_BOTTOM_CONNECTOR},
            {CONNECTS_LEFT | CONNECTS_RIGHT | CONNECTS_UP, HORIZONTAL_TOP_CONNECTOR},

            {CONNECTS_LEFT | CONNECTS_RIGHT | CONNECTS_UP | CONNECTS_DOWN, CROSS_CONNECTOR}
        };

    }

    namespace TIME{
        inline constexpr static  unsigned int MILLISECOND = 1; 
        inline constexpr static  unsigned int SECOND = MILLISECOND * 1000;
        inline constexpr static  unsigned int MINUTE = SECOND * 60;
        inline constexpr static  unsigned int HOUR = MINUTE * 60;
    }

    // Inits with 'NOW()' when created
    class BUTTON_STATE{
    public:
        bool State = false;
        std::chrono::system_clock::time_point Capture_Time;

        BUTTON_STATE(bool state = false){
            Capture_Time = std::chrono::system_clock::now();
            State = state;
        }
    };

    namespace Constants{
        inline std::string ESC_CODE = "\e[";
        inline std::string SEPERATE = ";";
        inline std::string Text_Color = "38";
        inline std::string Back_Ground_Color = "48";
        inline std::string RESET_Text_Color;
        inline std::string RESET_Back_Ground_Color;
        inline std::string USE_RGB = "2";
        inline std::string END_COMMAND = "m";
        inline std::string CLEAR_SCREEN = ESC_CODE + "2J";
        inline std::string CLEAR_SCROLLBACK = ESC_CODE + "3J";
        inline std::string SET_CURSOR_TO_START = ESC_CODE + "H";
        inline std::string RESET_CONSOLE = ESC_CODE + "c";

        inline std::string EnableFeature(std::string command) { return ESC_CODE + "?" + command + "h"; }
        inline std::string DisableFeature(std::string command) { return ESC_CODE + "?" + command + "l"; }
 
        // Enable settings for ANSI
        inline std::string REPORT_MOUSE_HIGHLIGHTS = ESC_CODE + "1000";
        inline std::string REPORT_MOUSE_BUTTON_WHILE_MOVING = ESC_CODE + "1002";
        inline std::string REPORT_MOUSE_ALL_EVENTS = ESC_CODE + "1003";

        inline std::string MOUSE_CURSOR = "25";
        inline std::string SCREEN_CAPTURE = "47"; // 47l = restores screen, 47h = saves screen
        inline std::string ALTERNATIVE_SCREEN_BUFFER = "1049"; // 1049l = disables alternative buffer, 1049h = enables alternative buffer
        // End of enable settings for ANSI

        inline unsigned long long NON = (unsigned long long)1 << 0;
        inline unsigned long long ENTER = (unsigned long long)1 << 1;
        inline unsigned long long ESCAPE = (unsigned long long)1 << 2;
        inline unsigned long long BACKSPACE = (unsigned long long)1 << 3;
        inline unsigned long long TAB = (unsigned long long)1 << 4;
        inline unsigned long long UP = (unsigned long long)1 << 5;
        inline unsigned long long DOWN = (unsigned long long)1 << 6;
        inline unsigned long long LEFT = (unsigned long long)1 << 7;
        inline unsigned long long RIGHT = (unsigned long long)1 << 8;
        inline unsigned long long SPACE = (unsigned long long)1 << 9;
        inline unsigned long long SHIFT = (unsigned long long)1 << 10;
        inline unsigned long long ALT = (unsigned long long)1 << 11;
        inline unsigned long long CONTROL = (unsigned long long)1 << 12;
        inline unsigned long long SUPER = (unsigned long long)1 << 13;
        inline unsigned long long HOME = (unsigned long long)1 << 14;
        inline unsigned long long INSERT = (unsigned long long)1 << 15;
        inline unsigned long long DELETE = (unsigned long long)1 << 16;
        inline unsigned long long END = (unsigned long long)1 << 17;
        inline unsigned long long PAGE_UP = (unsigned long long)1 << 18;
        inline unsigned long long PAGE_DOWN = (unsigned long long)1 << 19;
        inline unsigned long long F0 = (unsigned long long)1 << 20;
        inline unsigned long long F1 = (unsigned long long)1 << 21;
        inline unsigned long long F2 = (unsigned long long)1 << 22;
        inline unsigned long long F3 = (unsigned long long)1 << 23;
        inline unsigned long long F4 = (unsigned long long)1 << 24;
        inline unsigned long long F5 = (unsigned long long)1 << 25;
        inline unsigned long long F6 = (unsigned long long)1 << 26;
        inline unsigned long long F7 = (unsigned long long)1 << 27;
        inline unsigned long long F8 = (unsigned long long)1 << 28;
        inline unsigned long long F9 = (unsigned long long)1 << 29;
        inline unsigned long long F10 = (unsigned long long)1 << 30;
        inline unsigned long long F11 = (unsigned long long)1 << 31;
        inline unsigned long long F12 = (unsigned long long)1 << 32;
        inline unsigned long long F13 = (unsigned long long)1 << 33;
        inline unsigned long long F14 = (unsigned long long)1 << 34;
        inline unsigned long long F15 = (unsigned long long)1 << 35;
        inline unsigned long long F16 = (unsigned long long)1 << 36;

        // Should not fucking exist bro!
        //inline unsigned long long SHIFT_TAB = (unsigned long long)1 << 37;


        //key_Press includes [a-z, A-Z] & [0-9]
        inline unsigned long long KEY_PRESS = (unsigned long long)1 << 38;

        // EASY MOUSE API
        inline unsigned long long MOUSE_LEFT_CLICKED = (unsigned long long)1 << 39;
        inline unsigned long long MOUSE_MIDDLE_CLICKED = (unsigned long long)1 << 40;
        inline unsigned long long MOUSE_RIGHT_CLICKED = (unsigned long long)1 << 41;

        // NOTE: These will be spammed until it is not pressed anymore!
        inline unsigned long long MOUSE_LEFT_PRESSED = (unsigned long long)1 << 42;
        inline unsigned long long MOUSE_MIDDLE_PRESSED = (unsigned long long)1 << 43;
        inline unsigned long long MOUSE_RIGHT_PRESSED = (unsigned long long)1 << 44;

        inline unsigned long long MOUSE_MIDDLE_SCROLL_UP = (unsigned long long)1 << 45;
        inline unsigned long long MOUSE_MIDDLE_SCROLL_DOWN = (unsigned long long)1 << 46;

        inline void Init();
    }
    
    namespace BUTTON_STATES{
        inline std::string ESC = "ECS";
        inline std::string F1 = "F1";
        inline std::string F2 = "F2";
        inline std::string F3 = "F3";
        inline std::string F4 = "F4";
        inline std::string F5 = "F5";
        inline std::string F6 = "F6";
        inline std::string F7 = "F7";
        inline std::string F8 = "F8";
        inline std::string F9 = "F9";
        inline std::string F10 = "F10";
        inline std::string F11 = "F11";
        inline std::string F12 = "F12";
        inline std::string PRTSC = "PRTSC";
        inline std::string SCROLL_LOCK = "SCROLL_LOCK";
        inline std::string PAUSE = "PAUSE";
        inline std::string SECTION = "SECTION";
        inline std::string BACKSPACE = "BACKSPACE";
        inline std::string TAB = "TAB";
        inline std::string ENTER = "ENTER";
        inline std::string CAPS = "CAPS";
        inline std::string SHIFT = "SHIFT";
        inline std::string CONTROL = "CTRL";
        inline std::string SUPER = "SUPER";
        inline std::string ALT = "ALT";
        inline std::string SPACE = "SPACE";
        inline std::string ALTGR = "ALTGR";
        inline std::string FN = "FN";
        inline std::string INS = "INS";
        inline std::string HOME = "HOME";
        inline std::string PAGE_UP = "PAGE_UP";
        inline std::string DELETE = "DELETE";
        inline std::string INSERT = "INSERT";
        inline std::string END = "END";
        inline std::string PAGE_DOWN = "PAGE_DOWN";

        inline std::string UP = "UP";
        inline std::string DOWN = "DOWN";
        inline std::string LEFT = "LEFT";
        inline std::string RIGHT = "RIGHT";

        inline std::string MOUSE_LEFT = "MOUSE_LEFT";
        inline std::string MOUSE_MIDDLE = "MOUSE_MIDDLE";
        inline std::string MOUSE_RIGHT = "MOUSE_RIGHT";
    };

    inline std::map<std::string, unsigned long long> BUTTON_STATES_TO_CONSTANTS_BRIDGE = {

        {BUTTON_STATES::ESC, Constants::ESCAPE},
        {BUTTON_STATES::F1, Constants::F1},
        {BUTTON_STATES::F2, Constants::F2},
        {BUTTON_STATES::F3, Constants::F3},
        {BUTTON_STATES::F4, Constants::F4},
        {BUTTON_STATES::F5, Constants::F5},
        {BUTTON_STATES::F6, Constants::F6},
        {BUTTON_STATES::F7, Constants::F7},
        {BUTTON_STATES::F8, Constants::F8},
        {BUTTON_STATES::F9, Constants::F9},
        {BUTTON_STATES::F10, Constants::F10},
        {BUTTON_STATES::F11, Constants::F11},
        {BUTTON_STATES::F12, Constants::F12},
        //{BUTTON_STATES::PRTSC, Constants::PRINT_SCREEN},
        //{BUTTON_STATES::SCROLL_LOCK, Constants::SCROLL_LOCK},
        //{BUTTON_STATES::PAUSE, Constants::PAUSE},
        //{BUTTON_STATES::SECTION, Constants::SECTION},
        {BUTTON_STATES::BACKSPACE, Constants::BACKSPACE},
        {BUTTON_STATES::TAB, Constants::TAB},
        {BUTTON_STATES::ENTER, Constants::ENTER},
        //{BUTTON_STATES::CAPS, Constants::CAPS},
        {BUTTON_STATES::SHIFT, Constants::SHIFT},
        {BUTTON_STATES::CONTROL, Constants::CONTROL},
        {BUTTON_STATES::SUPER, Constants::SUPER},
        {BUTTON_STATES::ALT, Constants::ALT},
        {BUTTON_STATES::SPACE, Constants::SPACE},
        //{BUTTON_STATES::ALTGR, Constants::ALTGR},
        //{BUTTON_STATES::FN, Constants::FN},
        {BUTTON_STATES::INS, Constants::INSERT},
        {BUTTON_STATES::HOME, Constants::HOME},
        {BUTTON_STATES::PAGE_UP, Constants::PAGE_UP},
        {BUTTON_STATES::DELETE, Constants::DELETE},
        {BUTTON_STATES::INSERT, Constants::INSERT},
        {BUTTON_STATES::END, Constants::END},
        {BUTTON_STATES::PAGE_DOWN, Constants::PAGE_DOWN},

        {BUTTON_STATES::UP, Constants::UP},
        {BUTTON_STATES::DOWN, Constants::DOWN},
        {BUTTON_STATES::LEFT, Constants::LEFT},
        {BUTTON_STATES::RIGHT, Constants::RIGHT},

        {BUTTON_STATES::MOUSE_LEFT, Constants::MOUSE_LEFT_CLICKED},
        {BUTTON_STATES::MOUSE_MIDDLE, Constants::MOUSE_MIDDLE_CLICKED},
        {BUTTON_STATES::MOUSE_RIGHT, Constants::MOUSE_RIGHT_CLICKED}
    };

    class RGB{
    public:
        union{
            unsigned char Red = 0;
            unsigned char R;
        };
        union{
            unsigned char Green = 0;
            unsigned char G;
        };
        union{
            unsigned char Blue = 0;
            unsigned char B;
        };

        constexpr RGB(unsigned char r, unsigned char g, unsigned char b){
            R = r;
            G = g;
            B = b;
        }

        constexpr RGB(){}

        std::string Get_Colour() const{
            return std::to_string(Red) + Constants::SEPERATE + std::to_string(Green) + Constants::SEPERATE + std::to_string(Blue);
        }
    
        std::string Get_Over_Head(bool Is_Text_Color = true) const{
            if(Is_Text_Color){
                return Constants::ESC_CODE + Constants::Text_Color + Constants::SEPERATE + Constants::USE_RGB + Constants::SEPERATE;
            }
            else{
                return Constants::ESC_CODE + Constants::Back_Ground_Color + Constants::SEPERATE + Constants::USE_RGB + Constants::SEPERATE;
            }
        }
    
        bool operator==(const RGB& Other) const{
            return (Red == Other.Red) && (Green == Other.Green) && (Blue == Other.Blue);
        }
    
        RGB operator+(const RGB& Other) const{
            return RGB(Red + Other.Red, Green + Other.Green, Blue + Other.Blue);
        }
    
    };

    class RGBA : public RGB{
    private:
    // Ranging from 0. - 1.
        float Fast_Alpha = 1;

        union{
            unsigned char Alpha = std::numeric_limits<unsigned char>::max();
            unsigned char A;
        };
    public:

        void Set_Alpha(unsigned char a){
            Alpha = a;
            Fast_Alpha = (float)Alpha / std::numeric_limits<unsigned char>::max();
        }

        void Set_Alpha(float a){
            Fast_Alpha = a;
            Alpha = (unsigned char)(a * std::numeric_limits<unsigned char>::max());
        }

        RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0){
            R = r;
            G = g;
            B = b;
            Set_Alpha(a);
        }

        RGBA(){}

        RGBA(RGB primal){
            R = primal.R;
            G = primal.G;
            B = primal.B;
        }

        float &Get_Float_Alpha(){
            return Fast_Alpha;
        }

        unsigned char &Get_Alpha(){
            return Alpha;
        }
    
        bool operator==(const RGBA& Other){
            return (Red == Other.Red) && (Green == Other.Green) && (Blue == Other.Blue) && (Alpha == Other.Alpha);
        }

        RGBA operator*(const RGBA& Other){
            // Make the reverse alpha
            float Reverse_Alpha = 1 - Other.Fast_Alpha;
            
            return RGBA(
                ((float)this->Red * Reverse_Alpha) * ((float)Other.Red * Other.Fast_Alpha), 
                ((float)this->Green * Reverse_Alpha) * ((float)Other.Green * Other.Fast_Alpha), 
                ((float)this->Blue * Reverse_Alpha) * ((float)Other.Blue * Other.Fast_Alpha),
                Fast_Alpha
            );
        }

        RGBA operator+(const RGBA& Other){
            // Make the reverse alpha
            float Reverse_Alpha = 1 - Other.Fast_Alpha;

            return RGBA(
                ((float)this->Red * Reverse_Alpha) + ((float)Other.Red * Other.Fast_Alpha), 
                ((float)this->Green * Reverse_Alpha) + ((float)Other.Green * Other.Fast_Alpha), 
                ((float)this->Blue * Reverse_Alpha) + ((float)Other.Blue * Other.Fast_Alpha),
                Fast_Alpha
            );
        }

        RGBA operator*=(const RGBA& Other){
            // Make the reverse alpha
            float Reverse_Alpha = 1 - Other.Fast_Alpha;

            this->Red = ((float)this->Red * Reverse_Alpha) * ((float)Other.Red * Other.Fast_Alpha);
            this->Green = ((float)this->Green * Reverse_Alpha) * ((float)Other.Green * Other.Fast_Alpha);
            this->Blue = ((float)this->Blue * Reverse_Alpha) * ((float)Other.Blue * Other.Fast_Alpha);

            return *this;
        }

        RGBA operator+=(const RGBA& Other){

            // Calculate the divider which is by default 2, but gets smaller the less the Fast_Alpha is.
            // Fast_Alpha ranges from 0 to 1.

            // Make the reverse alpha
            float Reverse_Alpha = 1 - Other.Fast_Alpha;

            this->Red = ((float)this->Red * Reverse_Alpha) + ((float)Other.Red * Other.Fast_Alpha);
            this->Green = ((float)this->Green * Reverse_Alpha) + ((float)Other.Green * Other.Fast_Alpha);
            this->Blue = ((float)this->Blue * Reverse_Alpha) + ((float)Other.Blue * Other.Fast_Alpha);

            // float Divider = 1 + Other.Fast_Alpha;

            // Red = ((float)Red + ((float)Other.Red * (float)Other.Fast_Alpha)) / Divider;
            // Green = ((float)Green + ((float)Other.Green * (float)Other.Fast_Alpha)) / Divider;
            // Blue = ((float)Blue + ((float)Other.Blue * (float)Other.Fast_Alpha)) / Divider;

            // Red += ((float)Other.Red * (float)Other.Fast_Alpha);
            // Green += ((float)Other.Green * (float)Other.Fast_Alpha);
            // Blue += ((float)Other.Blue * (float)Other.Fast_Alpha);
            return *this;
        }

    };

    namespace COLOR{
        static const RGB WHITE = RGB(255, 255, 255);
        static const RGB BLACK = RGB(0, 0, 0);
        static const RGB RED = RGB(255, 0, 0);
        static const RGB GREEN = RGB(0, 255, 0);
        static const RGB BLUE = RGB(0, 0, 255);
        static const RGB YELLOW = RGB(255, 255, 0);
        static const RGB CYAN = RGB(0, 255, 255);
        static const RGB MAGENTA = RGB(255, 0, 255);
        static const RGB GRAY = RGB(128, 128, 128);
        static const RGB LIGHT_RED = RGB(255, 0, 0);
        static const RGB LIGHT_GREEN = RGB(0, 255, 0);
        static const RGB LIGHT_BLUE = RGB(0, 0, 255);
        static const RGB LIGHT_YELLOW = RGB(255, 255, 0);
        static const RGB LIGHT_CYAN = RGB(0, 255, 255);
        static const RGB LIGHT_MAGENTA = RGB(255, 0, 255);
        static const RGB LIGHT_GRAY = RGB(192, 192, 192);
        static const RGB DARK_RED = RGB(128, 0, 0);
        static const RGB DARK_GREEN = RGB(0, 128, 0);
        static const RGB DARK_BLUE = RGB(0, 0, 128);
        static const RGB DARK_YELLOW = RGB(128, 128, 0);
        static const RGB DARK_CYAN = RGB(0, 128, 128);
        static const RGB DARK_MAGENTA = RGB(128, 0, 128);
        static const RGB DARK_GRAY = RGB(64, 64, 64);
    }

    void Constants::Init(){
        RESET_Text_Color = ESC_CODE + Text_Color + SEPERATE + USE_RGB + SEPERATE + RGB(255, 255, 255).Get_Colour() + END_COMMAND;
        RESET_Back_Ground_Color = ESC_CODE + Back_Ground_Color + SEPERATE + USE_RGB + SEPERATE + RGB(0, 0, 0).Get_Colour() + END_COMMAND;
    }

    class Vector2{
    public:
        float X = 0;
        float Y = 0;

        Vector2(float x, float y){
            X = x;
            Y = y;
        }

        Vector2(){}

        Vector2 operator+(float num){
            return Vector2(X + num, Y + num);
        }

        Vector2 operator-(float num){
            return Vector2(X - num, Y - num);
        }

        Vector2 operator*(float num){
            return Vector2(X * num, Y * num);
        }
    };

    class Vector3 : public Vector2{
    public:
        float Z = 0;

        Vector3(float x, float y, float z){
            Z = z;
            X = x;
            Y = y;
        }

        Vector3(){}
    };

    class Coordinates{
    public:
        int X = 0;  //Horizontal
        int Y = 0;  //Vertical
        int Z = 0;  //priority (the higher the more likely it will be at top).

        Coordinates(int x = 0, int y = 0, int z = 0){
            X = x;
            Y = y;
            Z = z;
        }

        void operator+=(Coordinates* other){
            X += other->X;
            Y += other->Y;
            Z += other->Z;
        }

        void operator+=(Vector2 other){
            X += other.X;
            Y += other.Y;
        }
    };

    class UTF{
    public:
        bool Is_Unicode = false;

        char Ascii = ' ';
        std::string Unicode = " ";

        RGBA Foreground = {0, 0, 0}; 
        RGBA Background = {0, 0, 0};

        UTF(){}

        ~UTF(){}

        UTF(char data, std::pair<RGB, RGB> color = {{}, {}}){
            Ascii = data;
            Foreground = {color.first};
            Background = {color.second};
        }

        UTF(std::string data, std::pair<RGB, RGB> color = {{}, {}}){
            Unicode = data;
            Foreground = {color.first};
            Background = {color.second};
            Is_Unicode = true;
        }

        void Set_Foreground(RGB color){
            Foreground = {color};
        }

        void Set_Background(RGB color){
            Background = {color};
        }

        void Set_Color(std::pair<RGB, RGB> primals){
            Foreground = {primals.first};
            Background = {primals.second};
        }

        void Set_Text(std::string data){
            Unicode = data;
            Is_Unicode = true;
        }

        void Set_Text(char data){
            Ascii = data;
            Is_Unicode = false;
        }

        void Set_Text(UTF other){
            Ascii = other.Ascii;
            Unicode = other.Unicode;
            Is_Unicode = other.Is_Unicode;
        }

        std::string To_String();

        void operator=(char text){
            Set_Text(text);
        }

        void operator=(std::string text){
            Set_Text(text);
        }

        bool Has_Non_Default_Text(){
            return (Ascii != ' ') || (Unicode != " ");
        }

    };

    class Event{
    public:
        unsigned long long Criteria;
    };

    class Input : public Event{
    public:
        char Data = 0;
        unsigned int X = 0;
        unsigned int Y = 0;
        int Scale = 1;

        // The input information like the character written.
        Input(char d, unsigned long long t){
            Data = d;
            Criteria = t;
        }

        Input(Coordinates c, unsigned long long t, int s = 1){
            X = c.X;
            Y = c.Y;
            Criteria = t;
            Scale = s;
        }
    };

    class Action : public Event{
    public:
        class Element* Host;

        std::function<bool(GGUI::Event* e)> Job;
    
        Action(){}
        Action(unsigned long long criteria, std::function<bool(GGUI::Event* e)> job){
            Criteria = criteria;
            Job = job;
        }

        Action(unsigned long long criteria, std::function<bool(GGUI::Event* e)> job, class Element* host){
            Criteria = criteria;
            Job = job;
            Host = host;
        }
    };

    class Memory : public Action{
    public:
        std::chrono::high_resolution_clock::time_point Start_Time;
        size_t End_Time = 0;

        // By default all memories automatically will not prolong each other similar memories.
        bool Prolong_Memory = false;

        // When the job starts, job, prolong previous similar job by this time.
        Memory(size_t end, std::function<bool(GGUI::Event* e)>job, bool prolong = false){
            Start_Time = std::chrono::high_resolution_clock::now();
            End_Time = end;
            Job = job;
            Prolong_Memory = prolong;
        }
    };

    class Margin{
    public:
        unsigned int Top = 0;
        unsigned int Bottom = 0;
        unsigned int Left = 0;
        unsigned int Right = 0;

        Margin(unsigned int top = 0, unsigned int bottom = 0, unsigned int left = 0, unsigned int right = 0){
            Top = top;
            Bottom = bottom;
            Left = left;
            Right = right;
        }
    };

    enum class VALUE_TYPES{
        UNDEFINED,
        NUMBER,
        RGB,
        BOOL,
        COORDINATES,
        MARGIN,
    };

    class VALUE{
    public:
        VALUE_TYPES Type = VALUE_TYPES::UNDEFINED;

        VALUE(){}

        virtual VALUE* Copy() {
            return nullptr;
        };

        // Default VALUE wont do any parsing.
        static VALUE* Parse(std::string val){
            return nullptr;
        }  
    };

    class NUMBER_VALUE : public VALUE{
    public:
        int Value = 0;

        NUMBER_VALUE(int value){
            Value = value;
            Type = VALUE_TYPES::NUMBER;
        }

        NUMBER_VALUE(){
            Type = VALUE_TYPES::NUMBER;
        }

        VALUE* Copy() override {
            NUMBER_VALUE* copy = new NUMBER_VALUE(Value);
            return copy;
        } 
    };

    class RGB_VALUE : public VALUE{
    public:
        RGB Value = RGB();

        RGB_VALUE(RGB value){
            Value = value;
            Type = VALUE_TYPES::RGB;
        }

        RGB_VALUE(){
            Type = VALUE_TYPES::RGB;
        }

        VALUE* Copy() override {
            RGB_VALUE* copy = new RGB_VALUE(Value);
            return copy;
        } 
    };

    class BOOL_VALUE : public VALUE{
    public:
        bool Value = false;

        BOOL_VALUE(bool value){
            Value = value;
            Type = VALUE_TYPES::BOOL;
        }

        BOOL_VALUE(){
            Type = VALUE_TYPES::BOOL;
        }

        VALUE* Copy() override {
            BOOL_VALUE* copy = new BOOL_VALUE(Value);
            return copy;
        } 
    };

    class COORDINATES_VALUE : public VALUE{
    public:
        Coordinates Value = Coordinates();

        COORDINATES_VALUE(Coordinates value){
            Value = value;
            Type = VALUE_TYPES::COORDINATES;
        }

        COORDINATES_VALUE(){
            Type = VALUE_TYPES::COORDINATES;
        }

        VALUE* Copy() override {
            COORDINATES_VALUE* copy = new COORDINATES_VALUE(Value);
            return copy;
        } 
    };

    class MARGIN_VALUE : public VALUE{
    public:
        Margin Value = Margin();

        MARGIN_VALUE(){
            Type = VALUE_TYPES::MARGIN;
        }

        MARGIN_VALUE(Margin value){
            Value = value;
            Type = VALUE_TYPES::MARGIN;
        }

        VALUE* Copy() override {
            MARGIN_VALUE* copy = new MARGIN_VALUE(Value);
            return copy;
        } 
    };

    class SHADOW_VALUE : public VALUE{
    public:
        Vector3 Direction = {0, 0, 0.5};
        RGB Color = {};
        float Opacity = 1;

        SHADOW_VALUE(){}
    };

    namespace STYLES{
        inline std::string Border                           = "Border";
        inline std::string Text_Color                       = "Text_Color";
        inline std::string Background_Color                 = "Background_Color";
        inline std::string Border_Colour                    = "Border_Colour";
        inline std::string Border_Background_Color          = "Border_Background_Color";

        inline std::string Hover_Border_Color               = "Hover_Border_Color";
        inline std::string Hover_Text_Color                 = "Hover_Text_Color";
        inline std::string Hover_Background_Color           = "Hover_Background_Color";
        inline std::string Hover_Border_Background_Color    = "Hover_Border_Background_Color";

        inline std::string Focus_Border_Color               = "Focus_Border_Color";
        inline std::string Focus_Text_Color                 = "Focus_Text_Color";
        inline std::string Focus_Background_Color           = "Focus_Background_Color";
        inline std::string Focus_Border_Background_Color    = "Focus_Border_Background_Color";

        inline std::string Flow_Priority                    = "Flow_Priority";
        inline std::string Wrap                             = "Wrap";     
        
        inline std::string Text_Position                    = "Text_Position";
        inline std::string Allow_Input_Overflow             = "Allow_Input_Overflow";
        inline std::string Allow_Dynamic_Size               = "Allow_Dynamic_Size"; // boolean, Tries to emulate the size of the parent like in 'Flexbox: Display;' 
        inline std::string Margin                           = "Margin";

        inline std::string Shadow                           = "Shadow";  // 0 - 100
        inline std::string Opacity                          = "Opacity"; // 0 - 100

        inline std::string Anchor                           = "Anchor";  // gives the line number in which the element is anchored.

        inline std::string Allow_Scrolling                  = "Allow_Scrolling";
    };

    enum class STAIN_TYPE{
        CLEAN = 0,        //No change
        COLOR = 1 << 0,  //BG and other color related changes
        EDGE = 1 << 1,   //title and border changes.
        DEEP = 1 << 2,   //children changes. Deep because the childs are connected via AST.
        STRECH = 1 << 3,  //width and or height changes.
        TEXT = 1 << 4,   //text changes, this is primarily for text_field
        CLASS = 1 << 5, //This is used to tell the renderer that there are still un_parsed classes.
        STATE = 1 << 6, // This is for Switches that based on their state display one symbol differently.
        MOVE = 1 << 7, // This is for elements that are moved.
    };
 
    inline unsigned int operator|(STAIN_TYPE a, STAIN_TYPE b){
        return (unsigned int)a | (unsigned int)b;
    }

    inline unsigned int operator|(STAIN_TYPE a, unsigned int b){
        return (unsigned int)a | b;
    }

    inline unsigned int operator|(unsigned int a, STAIN_TYPE b){
        return a | (unsigned int)b;
    }

    class STAIN{
    public:
        STAIN_TYPE Type = STAIN_TYPE::CLEAN; //(STAIN_TYPE)(STAIN_TYPE::COLOR | STAIN_TYPE::EDGE | STAIN_TYPE::DEEP | STAIN_TYPE::STRECH | STAIN_TYPE::CLASS | STAIN_TYPE::MOVE);


        bool is(STAIN_TYPE f){
            if (f == STAIN_TYPE::CLEAN){
                return Type <= f;
            }
            return ((unsigned int)Type & (unsigned int)f) == (unsigned int)f;
        }

        void Clean(STAIN_TYPE f){
            Type = (STAIN_TYPE)((unsigned int)Type & ~(unsigned int)f);
        }

        void Clean(unsigned int f){
            Type = (STAIN_TYPE)((unsigned int)Type & ~f);
        }

        void Dirty(STAIN_TYPE f){
            Type = (STAIN_TYPE)((unsigned int)Type | (unsigned int)f);
        }

        void Dirty(unsigned int f){
            Type = (STAIN_TYPE)((unsigned int)Type | f);
        }

        // void Stain_All(){
        //     Dirty(STAIN_TYPE::COLOR | STAIN_TYPE::EDGE | STAIN_TYPE::DEEP | STAIN_TYPE::STRECH | STAIN_TYPE::CLASS | STAIN_TYPE::MOVE);
        // }

    };

    enum class Flags{
        Empty = 0,
        Border = 1 << 0,
        Text_Input = 1 << 1,
        Overflow = 1 << 2,
        Dynamic = 1 << 3,
        Horizontal = 1 << 4,
        Vertical = 1 << 5,
        Align_Left = 1 << 6,
        Align_Right = 1 << 7,
        Align_Center = 1 << 8,
    };
    
    inline Flags operator|(Flags a, Flags b){
        return static_cast<Flags>(static_cast<int>(a) | static_cast<int>(b));
    }

    inline bool Is(Flags a, Flags b){
        return ((int)a & (int)b) == (int)b;
    }

    inline bool Has(Flags a, Flags b){
        return ((int)a & (int)b) != 0;
    }

    enum class State{
        UNKNOWN,

        RENDERED,
        HIDDEN

    };

    namespace SETTINGS{
        // How fast for a detection of hold down situation.
        inline unsigned long long Mouse_Press_Down_Cooldown = 365;
        inline unsigned long long Input_Clear_Time = 16;
        inline bool Word_Wrapping = true;
    };
  
    // For templates.
    extern std::vector<Action*> Event_Handlers;

    class Element{
    protected:
        Coordinates Position;

        unsigned int Width = 1;
        unsigned int Height = 1;

        unsigned int Post_Process_Width = 0;
        unsigned int Post_Process_Height = 0;

        //INTERNAL FLAGS
        class Element* Parent = nullptr;
        bool Show = true;
        
        std::vector<UTF> Render_Buffer;
        STAIN Dirty;
        
        std::vector<int> Classes;

        std::vector<Element*> Childs;

        bool Focused = false;
        bool Hovered = false;

        std::string Name = "";

        std::map<std::string, VALUE*> Style;

        std::map<State, std::function<void()>> State_Handlers;
    public:

        Element();

        Element(std::string Class, unsigned int width = 0, unsigned int height = 0, Element* parent = nullptr, Coordinates *position = nullptr);

        Element(std::map<std::string, VALUE*> css, unsigned int width = 0, unsigned int height = 0, Element* parent = nullptr, Coordinates *position = nullptr);

        Element(
            unsigned int width,
            unsigned int height,
            Coordinates position
        );

        //These next constructors are mainly for users to more easily create elements.
        Element(
            unsigned int width,
            unsigned int height
        );

        Element(
            unsigned int width,
            unsigned int height,
            RGB text_color,
            RGB background_color
        );

        Element(
            unsigned int width,
            unsigned int height,
            RGB text_color,
            RGB background_color,
            RGB border_color,
            RGB border_background_color
        );

        // Disable Copy constructor
        Element(const Element&);

        //Start of destructors.
        //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

        ~Element();

        //
        //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
                
        virtual Element* Safe_Move(){
            Element* new_element = new Element();
            *new_element = *(Element*)this;

            return new_element;
        }

        // USe this when you want to duplicate the same element with its properties safely.
        Element* Copy();

        virtual void Fully_Stain();

        // If you want to make a representing element* that isnt the same as the Abstract one.
        // Then Remember to USE THIS!
        void Inherit_States_From(Element* abstract);

        void Parse_Classes();

        STAIN& Get_Dirty(){
            return Dirty;
        }

        bool Is_Focused(){
            return Focused;
        }

        void Set_Focus(bool f);

        bool Is_Hovered(){
            return Hovered;
        }

        void Set_Hover_State(bool h);

        void Check(State s);

        std::map<std::string, VALUE*> Get_Style();

        void Set_Style(std::map<std::string, VALUE*> css);

        virtual Element* Handle_Or_Operator(Element* other){
            Set_Style(other->Get_Style());
        }

        void Add_Class(std::string class_name);

        RGB Get_RGB_Style(std::string style_name);

        int Get_Number_Style(std::string style_name);

        bool Get_Bool_Style(std::string style_name);

        VALUE* Get_Style(std::string style_name);

        void Set_Style(std::string style_name, VALUE* value);

        // Takes 0.0f to 1.0f
        void Set_Opacity(float Opacity);

        // RGBA - Alpha channel. 0 - 255
        void Set_Opacity(unsigned char Opacity);

        // return int as 0 - 100
        int Get_Opacity(); 

        bool Is_Transparent();

        bool Is_Anchored();

        int Get_Anchor_Location();

        void Set_Anchor_At_Current_Location();

        void Remove_Anchor();

        unsigned int Get_Processed_Width();
        unsigned int Get_Processed_Height();

        // Direction: Unsupported atm!!!
        void Show_Shadow(Vector2 Direction, RGB Shadow_Color, float Opacity = 1, float Length = 0.5);

        void Show_Shadow(RGB Shadow_Color, float Opacity = 1, float Length = 0.5);

        Element* Get_Parent(){
            return Parent;
        }

        void Set_Parent(Element* parent);

        bool Has(std::string s);

        bool Has(int s){
            for (auto i : Classes){
                if (i == s)
                    return true;
            }
            return false;
        }

        //returns the area which a new element could be fitted in.
        std::pair<unsigned int, unsigned int> Get_Fitting_Dimensions(Element* child);

        // returns the maximum area of width and height which an element could be fit in.
        // basically same as the Get_Fitting_Dimensions(), but with some extra safe checks, so use this.
        std::pair<unsigned int, unsigned int> Get_Limit_Dimensions();

        virtual void Show_Border(bool b);

        virtual void Show_Border(bool b, bool Previus_state);

        bool Has_Border();

        void Display(bool f);

        bool Is_Displayed();

        virtual void Add_Child(Element* Child);

        virtual void Set_Childs(std::vector<Element*> childs);

        bool Children_Changed();
        
        bool Has_Transparent_Children();

        std::vector<Element*>& Get_Childs();

        virtual bool Remove(Element* handle);

        bool Remove(int index);

        void Set_Dimensions(int width, int height);

        int Get_Width();

        int Get_Height();

        void Set_Width(int width);

        void Set_Height(int height);

        void Set_Position(Coordinates c);
       
        void Set_Position(Coordinates* c);

        Coordinates Get_Position();

        Coordinates Get_Absolute_Position();

        void Set_Margin(Margin margin);

        Margin Get_Margin();

        void Set_Background_Color(RGB color);

        RGB Get_Background_Color();
        
        void Set_Border_Color(RGB color);
        
        RGB Get_Border_Color();

        void Set_Border_Background_Color(RGB color);
        
        RGB Get_Border_Background_Color();
        
        void Set_Text_Color(RGB color);

        void Allow_Dynamic_Size(bool True);
        
        RGB Get_Text_Color();

        static std::pair<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>> Get_Fitting_Area(GGUI::Element* Parent, GGUI::Element* Child);

        void Compute_Dynamic_Size();

        virtual std::vector<UTF> Render();

        // Used to update the parent when the child cannot update on itself, for an example on removal of an element.
        virtual void Update_Parent(Element* New_Element);

        virtual void Add_Overhead(Element* w, std::vector<UTF>& Result);

        virtual void Apply_Colors(Element* w, std::vector<UTF>& Result);

        virtual bool Resize_To(Element* parent){
            return false;
        }

        void Compute_Alpha_To_Nesting(GGUI::UTF& Dest, GGUI::UTF Source);

        void Nest_Element(Element* Parent, Element* Child, std::vector<UTF>& Parent_Buffer, std::vector<UTF> Child_Buffer);

        void Post_Process_Borders(Element* A, Element* B, std::vector<UTF>& Parent_Buffer);

        std::pair<RGB, RGB>  Compose_All_Text_RGB_Values();

        RGB  Compose_Text_RGB_Values();
        RGB  Compose_Background_RGB_Values(bool Get_As_Foreground = false);

        std::pair<RGB, RGB>  Compose_All_Border_RGB_Values();

        virtual std::string Get_Name() const {
            return "Element<" + Name + ">";
        }

        void Set_Name(std::string name);

        bool Has_Internal_Changes();

        //Makes suicide.
        void Remove();

        //Event handlers
        void On_Click(std::function<bool(GGUI::Event* e)> action);

        void On(unsigned long long criteria, std::function<bool(GGUI::Event* e)> action, bool GLOBAL = false);

        //This function returns nullptr, if the element could not be found.
        Element* Get_Element(std::string name);

        // TEMPLATES
        //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

        //This function returns all child elements that have the same element type.
        template<typename T>
        std::vector<T*> Get_Elements(){

            //go throgh the child AST, and check if the element in question is same type as the template T.
            std::vector<T*> result;

            if (typeid(*this) == typeid(T)){
                result.push_back((T*)this);
            }

            for (auto e : Childs){
                std::vector<T*> child_result = e->Get_Elements<T>();
                result.insert(result.end(), child_result.begin(), child_result.end());
            }

            return result;
        }

        template<typename T>
        T* At(std::string s){
            T* v = (T*)Style[s];

            if (v == nullptr){
                v = new T();

                Style[s] = v;
            }

            return v;
        }

        //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

        void Re_Order_Childs();

        void Focus();

        void On_State(State s, std::function<void()> job);

        std::vector<GGUI::UTF> Process_Shadow(std::vector<GGUI::UTF> Current_Buffer);

        std::vector<GGUI::UTF> Process_Opacity(std::vector<GGUI::UTF> Current_Buffer);

        virtual std::vector<GGUI::UTF> Postprocess();

    };

    enum class TEXT_LOCATION{
        LEFT,
        CENTER,
        RIGHT,
    };

    class Text_Field : public Element{
    protected:
        std::string Data = "";
        std::string Previus_Data = "";
        bool Allow_Text_Input = false;
        
    public:

        Text_Field(){}

        Text_Field(std::string Text, std::map<std::string, VALUE*> css = {});

        //These next constructors are mainly for users to more easily create elements.

        Text_Field(
            std::string Text,
            RGB text_color,
            RGB background_color
        );

        Text_Field(
            std::string Text,
            RGB text_color,
            RGB background_color,
            RGB border_color,
            RGB border_background_color
        );

        //End of user constructors.

        void Fully_Stain() override;

        void Set_Data(std::string Data);

        std::string Get_Data();

        void Set_Text_Position(TEXT_LOCATION Text_Position);

        TEXT_LOCATION Get_Text_Position();
        
        void Show_Border(bool state) override;
        
        static std::pair<unsigned int, unsigned int> Get_Text_Dimensions(std::string& text); 

        std::vector<UTF> Render() override;
        
        bool Resize_To(Element* parent) override;

        std::string Get_Name() const override;

        //async function, 
        void Input(std::function<void(char)> Then);

        void Enable_Text_Input();

        void Disable_Text_Input();

        bool Is_Input_Allowed(){
            return Allow_Text_Input;
        }

        //Non visual updates dont need to update frame
        void Enable_Input_Overflow();

        //Non visual updates dont need to update frame
        void Disable_Input_Overflow();

        void Enable_Dynamic_Size();

        void Disable_Dynamic_Size();

        static void Center_Text(GGUI::Element* self, std::string Text, GGUI::Element* wrapper, std::vector<GGUI::UTF>& Previus_Render);
        static void Left_Text(GGUI::Element* self, std::string Text, GGUI::Element* wrapper, std::vector<GGUI::UTF>& Previus_Render);
        static void Right_Text(GGUI::Element* self, std::string Text, GGUI::Element* wrapper, std::vector<GGUI::UTF>& Previus_Render);

        Element* Safe_Move() override {
            Text_Field* new_Text_Field = new Text_Field();
            *new_Text_Field = *(Text_Field*)this;

            return new_Text_Field;
        }
    };

    class Button : public Text_Field{
    protected:
        void Defualt_Button_Behaviour(std::function<void (Button* This)> press = [](Button* This){}){
            On_Click([=](Event* e){
                // The default, on_click wont do anything.
                press(this);

                return true;
            });
        }
    
        void Default_Button_Text_Align(){
            At<NUMBER_VALUE>(STYLES::Text_Position)->Value = (int)TEXT_LOCATION::CENTER;
        }

        // DONT USE AS USER!!
        Button(){}
    public:

        Button(std::string Text, std::function<void (Button* This)> press = [](Button* This){}) : Text_Field(Text){
            Defualt_Button_Behaviour(press);
            Default_Button_Text_Align();
            Enable_Input_Overflow();
            Dirty.Dirty(STAIN_TYPE::TEXT);
            Show_Border(true);
            Set_Name(Text);
        }

        Element* Safe_Move() override {
            Button* new_Button = new Button();
            *new_Button = *(Button*)this;

            return new_Button;
        }

        std::string Get_Name() const override{
            return "Button<" + Name + ">";
        }
    };

    class Canvas : public Element{
    private:
        // DONT GIVE THIS TO USER!
        Canvas(){}
    protected:
        std::vector<RGB> Buffer;
    public:
        Canvas(unsigned int w, unsigned int h, Coordinates position);
        
        // This is to set a color in the canvas, you can set it to not flush, if youre gonna set more than one pixel.
        void Set(unsigned int x, unsigned int y, RGB color, bool Flush = true);
        
        void Flush();

        std::vector<UTF> Render() override;

        Element* Safe_Move() override {
            Canvas* new_Canvas = new Canvas();
            *new_Canvas = *(Canvas*)this;

            return new_Canvas;
        }

        std::string Get_Name() const override{
            return "Canvas<" + Name + ">";
        }
    };

    class Sprite{
    public:
        RGB Background_Color;
        RGB Foreground_Color;
        UTF Texture;

        Sprite(UTF t = UTF(" "), RGB f = COLOR::WHITE, RGB b = COLOR::BLACK) : Texture(t), Foreground_Color(f), Background_Color(b){}

        UTF Render();
    };

    class Terminal_Canvas : public Element{
    private:
        // DONT GIVE THIS TO USER!!!
        Terminal_Canvas(){}
    protected:
        std::vector<Sprite> Buffer;
    public:
        Terminal_Canvas(unsigned int w, unsigned int h, Coordinates position);
        
        void Set(unsigned int x, unsigned int y, Sprite sprite, bool Flush = true);

        void Set(unsigned int x, unsigned int y, UTF sprite, bool Flush = true);
        
        void Flush();
        
        std::vector<UTF> Render() override;
        
        Element* Safe_Move() override {
            Terminal_Canvas* new_Terminal_Canvas = new Terminal_Canvas();
            *new_Terminal_Canvas = *(Terminal_Canvas*)this;

            return new_Terminal_Canvas;
        }

        std::string Get_Name() const override{
            return "Terminal_Canvas<" + Name + ">";
        }
    };

    enum class Grow_Direction{
        ROW,
        COLUMN
    };

    class List_View : public Element{
    public:
        //We can always assume that the list starts from the upper left corner, right?
        Element* Last_Child = new Element(0, 0, {0, 0});

        std::vector<std::pair<unsigned int, unsigned int>> Layer_Peeks;

        List_View(std::map<std::string, VALUE*> css = {}, unsigned int width = 0, unsigned int height = 0, Element* parent = nullptr, Coordinates position = {0, 0, 0});

        //These next constructors are mainly for users to more easily create elements.
        List_View(
            RGB text_color,
            RGB background_color
        );

        List_View(
            unsigned int width,
            unsigned int height,
            RGB text_color,
            RGB background_color
        );

        List_View(
            unsigned int width,
            unsigned int height,
            RGB text_color,
            RGB background_color,
            RGB border_color,
            RGB border_background_color
        );

        List_View(Element* parent, std::vector<Element*> Tree, Grow_Direction grow_direction = Grow_Direction::ROW);

        Element* Handle_Or_Operator(Element* other) override{
            Add_Child(other);
            return this;
        }

        //End of user constructors.

        void Add_Child(Element* e) override;
        
        //std::vector<UTF> Render() override;

        std::string Get_Name() const override;

        bool Remove(Element* e) override;

        void Set_Growth_Direction(Grow_Direction gd){
            At<NUMBER_VALUE>(STYLES::Flow_Priority)->Value = (int)gd;
        }

        Grow_Direction Get_Growth_Direction(){
            return (Grow_Direction)At<NUMBER_VALUE>(STYLES::Flow_Priority)->Value;
        }

        template<typename  T>
        T* Get(int index){
            if (index > Childs.size() - 1)
                return nullptr;

            if (index < 0)
                index = Childs.size() + index - 1;

            return (T*)this->Childs[index];
        }

        Element* Safe_Move() override {
            List_View* new_List_View = new List_View();
            *new_List_View = *(List_View*)this;

            return new_List_View;
        }

    };

    class Scroll_View : public Element{
    protected:
        unsigned int Scroll_Index = 0;  // Render based on the offset of the scroll_index by flow direction.

        List_View* Container = nullptr;
    public:

        // Constructors:
        // -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
        Scroll_View(Grow_Direction grow_direction = Grow_Direction::ROW);

        Scroll_View(List_View& container);

        Scroll_View(std::vector<Element*> Childs, Grow_Direction grow_direction = Grow_Direction::ROW);

        // Re-pipeline functions:
        // -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
        void Add_Child(Element* e) override;

        void Allow_Scrolling(bool allow);
    
        bool Is_Scrolling_Enabled(){
            return At<BOOL_VALUE>(STYLES::Allow_Scrolling)->Value;
        }

        void Scroll_Up();

        void Scroll_Down();
    };

    class Window : public Element{
        std::string Title = "";  //if this is empty then no title

        RGB Before_Hiding_Border_Color = COLOR::WHITE;
        RGB Before_Hiding_Border_Background_Color = COLOR::BLACK;
        bool Has_Hidden_Borders = false;
    public:
        Window() : Element() {}

        Window(std::string title, std::vector<std::string> classes = {});

        Window(std::map<std::string, VALUE*> css, unsigned int width = 0, unsigned int height = 0, Element* parent = nullptr, Coordinates* position = nullptr);
        
        Window(std::string title, std::map<std::string, VALUE*> css, unsigned int width = 0, unsigned int height = 0, Element* parent = nullptr, Coordinates* position = nullptr);

        //These next constructors are mainly for users to more easily create elements.
        Window(
            std::string title, 
            unsigned int width,
            unsigned int height
        );

        Window(
            std::string title, 
            unsigned int width,
            unsigned int height,
            RGB text_color,
            RGB background_color
        );

        Window(
            std::string title, 
            unsigned int width,
            unsigned int height,
            RGB text_color,
            RGB background_color,
            RGB border_color
        );

        Window(
            std::string title, 
            unsigned int width,
            unsigned int height,
            RGB text_color,
            RGB background_color,
            RGB border_color,
            RGB border_background_color
        );

        Window(
            std::string title,
            unsigned int width,
            unsigned int height,
            std::vector<Element*> Tree 
        );

        //End of user constructors.

        void Set_Title(std::string t);

        std::string Get_Title();
        
        void Add_Overhead(Element* w, std::vector<UTF>& Result) override;

        std::string Get_Name() const override;

        void Show_Border(bool state) override;

        void Show_Border(bool state, bool previus_state) override;

        Element* Safe_Move() override {
            Window* new_Window = new Window();
            *new_Window = *(Window*)this;

            return new_Window;
        }
    };

    class Switch : public Element{
    private:
        // DONT GIVE TO USER !!!
        Switch(){}
    protected:
        bool State = false;

        std::string Text = "";
        //COntains the unchecked version of the symbol and the checked version.
        std::vector<std::string> States;

    public:
        Switch(std::string text, std::vector<std::string> states, std::function<void (Element* This)> event = [](Element* e){});

        std::vector<UTF> Render() override;

        void Toggle(){
            State = !State;

            Dirty.Dirty(STAIN_TYPE::STATE);
        }

        std::string Get_Data() { return Text; }

        void Set_Data(std::string data) { Text = data; Dirty.Dirty(STAIN_TYPE::TEXT); }
        
        Element* Safe_Move() override {
            Switch* new_Switch = new Switch();
            *new_Switch = *(Switch*)this;

            return new_Switch;
        }

        std::string Get_Name() const override{
            return "Switch<" + Name + ">";
        }
    };

    class Radio_Button : public Switch{
    public:
        Radio_Button(std::string text) : Switch(text, {SYMBOLS::RADIOBUTTON_OFF, SYMBOLS::RADIOBUTTON_ON}){}

        bool Get_State(){
            return State;
        }
        
        // The Swtich overrides it for us.
        //Element* Safe_Move() override;
        
        std::string Get_Name() const override{
            return "Radio_Button<" + Name + ">";
        }
    };

    class Check_Box : public Switch{
    public:
        Check_Box(std::string text) : Switch(text, {SYMBOLS::EMPTY_CHECK_BOX, SYMBOLS::CHECKED_CHECK_BOX}){}

        bool Get_State(){
            return State;
        }
        
        // The Swtich overrides it for us.
        //Element* Safe_Move() override;

        std::string Get_Name() const override{
            return "Check_Box<" + Name + ">";
        }
    };

    class Progress_Bar : public Element{
    protected:
        float Progress = 0; // 0.0 - 1.0

        void Add_Horizontal_Lines(std::vector<UTF>& buffer);
        std::vector<UTF> Render() override;
        void Apply_Colors(Element* w, std::vector<UTF>& Result) override;
    public:
        void Set_Progress(float New_Progress);
        float Get_Progress();

        void Show_Border(bool state);

        void Set_Fill_Color(RGB value);
        void Set_Empty_Color(RGB value);
    
        Progress_Bar();
        Progress_Bar(unsigned int Width, unsigned int Height = 1);
        Progress_Bar(RGB Fill_Color, RGB Empty_Color);
        Progress_Bar(RGB Fill_COlor, RGB Empty_Color, unsigned int Width, unsigned int Height = 1);

        
        Element* Safe_Move() override {
            Progress_Bar* new_Progress_Bar = new Progress_Bar();
            *new_Progress_Bar = *(Progress_Bar*)this;

            return new_Progress_Bar;
        }

        std::string Get_Name() const override{
            return "Progress_Bar<" + Name + ">";
        }
    };

    /*
        Utilities to manage file streams.
    */

    class FILE_STREAM;

    extern std::unordered_map<std::string, FILE_STREAM*> File_Streamer_Handles;

    extern void Add_File_Stream_Handle(std::string File_Handle, std::function<void()> Handle);

    extern FILE_STREAM* Get_File_Stream_Handle(std::string File_Name);

    extern std::string Get_Current_Location();

    class FILE_STREAM{
    private:
        std::ifstream Handle;
        std::vector<std::function<void()>> On_Change = {};
        std::string Previous_Content = "";
        unsigned long long Previous_Hash = 0;
    public:
        std::string Name = "";

        FILE_STREAM(std::string File_Name, std::function<void()> on_change);

        ~FILE_STREAM(){
            Handle.close();
        }

        std::string Read();
    
        std::string Fast_Read() { return Previous_Content; }

        void Changed();

        void Add_On_Change_Handler(std::function<void()> on_change){
            On_Change.push_back(on_change);
        }
    };

    class FILE_POSITION{
    public:
        std::string File_Name = "";     // Originated.
        unsigned int Line_Number = 0;   // Y
        unsigned int Character = 0;     // X

        FILE_POSITION(std::string File_Name, unsigned int Line_Number, unsigned int Character){
            this->File_Name = File_Name;
            this->Line_Number = Line_Number;
            this->Character = Character;
        }

        FILE_POSITION() = default;

        std::string To_String(){
            return File_Name + ":" + std::to_string(Line_Number) + ":" + std::to_string(Character);
        }
    };

    
    class HTML : public Element{
    private:
        // DONT GIVE TO USER !!!
        HTML(){}
    private:
        FILE_STREAM* Handle = nullptr;
    public:
        HTML(std::string File_Name);

        Element* Safe_Move() override {
            HTML* new_HTML = new HTML();
            *new_HTML = *(HTML*)this;

            return new_HTML;
        }

        std::string Get_Name() const override{
            return "HTML<" + Name + ">";
        }
    };

    enum class HTML_GROUP_TYPES{
        UNKNOWN,
        TEXT,
        NUMBER,
        OPERATOR,   // =, 
        WRAPPER,    // <>, [], {}, (), "", ''
        SPACING,    // newline, ' ', '\t'
        ATTRIBUTE,  // Contains attributes as an wrapper extension. id="123"
    };

    enum class PARSE_BY{
        NONE                    = 0,
        TOKEN_WRAPPER           = 1 << 0,
        DYNAMIC_WRAPPER         = 1 << 1, 
        OPERATOR_PARSER         = 1 << 2,
        NUMBER_POSTFIX_PARSER   = 1 << 3,
    };

    enum class HTML_POSITION_TYPE{
        STATIC,     // Default positioning, like in GGUI.
        RELATIVE,   // Relative to parent.
        ABSOLUTE,   // Relative to screen.
        FIXED,      // Relative to screen, but does not move with scrolling.
        STICKY,     // Relative to screen until crosses given threshold.
    };

    extern PARSE_BY operator|(PARSE_BY first, PARSE_BY second);

    extern PARSE_BY operator&(PARSE_BY first, PARSE_BY second);

    extern void operator|=(PARSE_BY& first, PARSE_BY second);

    class HTML_Token{
    public:
        HTML_GROUP_TYPES Type = HTML_GROUP_TYPES::UNKNOWN;
        std::string Data = "";
        std::vector<HTML_Token*> Childs;    // also contains attributes!
        FILE_POSITION Position;

        PARSE_BY Parsed_By = PARSE_BY::NONE;

        HTML_Token(HTML_GROUP_TYPES Type, std::string Data){
            this->Type = Type;
            this->Data = Data;
        }

        HTML_Token(HTML_GROUP_TYPES Type, char Data, FILE_POSITION position){
            this->Type = Type;
            this->Data.push_back(Data);
            this->Position = position;
        }

        // Checks if the Parsed_By contains specific bit mask.
        bool Is(PARSE_BY f){
            return (Parsed_By & f) == f;
        }

        bool Has(PARSE_BY f){
            return (f & Parsed_By) > PARSE_BY::NONE;
        }

        HTML_Token() = default;
    };

    class HTML_Group{
    public:
        HTML_GROUP_TYPES Type = HTML_GROUP_TYPES::UNKNOWN;
        char Start = 0;
        char End = 0;
        bool Is_Sticky = true;

        HTML_Group(HTML_GROUP_TYPES Type, char Start, char End, bool Is_Sticky = true){
            this->Type = Type;
            this->Start = Start;
            this->End = End;
            this->Is_Sticky = Is_Sticky;
        }
    };

    class HTML_Node{
    public:
        std::string Tag_Name = "";  // DIV, HREF, etc...
        
        std::vector<HTML_Node*> Childs;
        HTML_Node* parent = nullptr;

        FILE_POSITION Position;

        HTML_Token* RAW = nullptr;
        HTML_GROUP_TYPES Type = HTML_GROUP_TYPES::UNKNOWN;

        // Postfixes are in child[0] for numbers.
        // Decimals are also number typed.
        // Operators left is Child[0] and Right at Child[1].
        // Attributes cannot be computed, before some contextual data on AST level is constructed, since the postfix operands depend on these kind of information from parent.
        std::unordered_map<std::string, GGUI::HTML_Token*> Attributes;    // contains ID, Name, Class, Color, BG_Color, etc...
    };

    extern void Parse(std::vector<HTML_Token*>& Input);

    extern std::vector<Element*> Parse_HTML(std::string Raw_Buffer, Element* parent);

    extern std::vector<HTML_Token*>& Parse_HTML(std::vector<HTML_Token*>& Input);

    extern void Parse_Embedded_Bytes(int& i, std::vector<HTML_Token*>& Input);

    extern void Parse_All_Wrappers(int& i, std::vector<HTML_Token*>& Input);

    extern void Parse_Dynamic_Wrappers(int& i, std::vector<HTML_Token*>& Input, std::string word);

    extern void Parse_Wrapper(std::string start_pattern, std::string end_pattern, int& i, std::vector<HTML_Token*>& Input);

    extern const std::vector<HTML_Group> Groups;

    extern std::vector<HTML_Token*> Lex_HTML(std::string Raw_Buffer);

    extern std::vector<HTML_Node*> Parse_Lexed_Tokens(std::vector<HTML_Token*> Input);

    extern std::unordered_map<std::string, std::function<GGUI::Element* (HTML_Node*)>>* HTML_Translators;

    extern std::unordered_map<std::string, double> POSTFIX_COEFFICIENT;

    extern std::unordered_map<std::string, void*> RELATIVE_COEFFICIENT;

    // helper functions
    #define CONCAT_IMPL(x, y) x##y
    #define CONCAT(x, y) CONCAT_IMPL(x, y)

    // For ease of use for adding translators for user custom HTML TAG parsers.
    #define GGUI_Add_Translator(id, handler) \
        auto CONCAT(_, __LINE__) = [](){ \
            if (GGUI::HTML_Translators == nullptr){ \
                GGUI::HTML_Translators = new std::unordered_map<std::string, std::function<GGUI::Element* (GGUI::HTML_Node*)>>(); \
            } \
            return GGUI::HTML_Translators->insert({id, handler}); \
        }();

    extern std::vector<Element*> Parse_Translators(std::vector<HTML_Node*>& Input);

    extern HTML_Node* Factory(HTML_Token* Input);

    extern void Parse_Numeric_Postfix(int& i, std::vector<HTML_Token*>& Input);

    extern void Parse_Decimal(int& i, std::vector<HTML_Token*>& Input);

    extern void Parse_Operator(int& i, std::vector<HTML_Token*>& Input, char operator_type);

    extern void Report(std::string problem, FILE_POSITION location);

    extern HTML_Node* Element_To_Node(Element* e);

    extern double Compute_Val(HTML_Token* val, HTML_Node* parent, std::string attr_name);

    extern double Compute_Operator(HTML_Token* op, HTML_Node* parent, std::string attr_name);

    extern double Compute_Post_Fix_As_Coefficient(std::string postfix, HTML_Node* parent, std::string attr_name);

    extern void Translate_Attributes_To_Element(Element* e, HTML_Node* input);

    extern void Translate_Childs_To_Element(Element* e, HTML_Node* input, std::string* Set_Text_To);

    extern std::vector<UTF> Abstract_Frame_Buffer;               //2D clean vector whitout bold nor color
    extern std::string Frame_Buffer;                                 //string with bold and color, this what gets drawn to console.
    extern std::atomic_bool Pause_Render;                     //if true, the render will not be updated, good for window creation.
    extern std::atomic_bool Pause_Event_Thread;                                 //Main window

    extern int Max_Width;
    extern int Max_Height;

    extern std::vector<Memory> Remember;

    extern std::vector<Action*> Event_Handlers;
    extern std::vector<Input*> Inputs;
    
    extern std::map<std::string, Element*> Element_Names;

    extern Element* Focused_On;
    extern Element* Hovered_On;

    extern Coordinates Mouse;    
    extern bool Mouse_Movement_Enabled;

    extern std::map<std::string, BUTTON_STATE> KEYBOARD_STATES;

    extern time_t UPDATE_SPEED_MIILISECONDS;
    extern int Inputs_Per_Second;
    extern int Inputs_Per_Query;

    extern std::map<int, std::map<std::string, VALUE*>> Classes;
    extern std::map<std::string, int> Class_Names;

    extern Window* Main;  
    extern std::unordered_map<int, Element*> Outboxed_Elements;

    void SLEEP(unsigned int seconds);

    extern bool Collides(GGUI::Element* a, GGUI::Element* b);

    extern bool Collides(GGUI::Element* a, GGUI::Coordinates b);

    extern bool Collides(GGUI::Element* a, GGUI::Coordinates c, unsigned int Width, unsigned int Height);

    extern Element* Get_Accurate_Element_From(Coordinates c, Element* Parent);

    extern Coordinates Find_Upper_Element();

    extern Coordinates Find_Lower_Element();

    extern Coordinates Find_Left_Element();

    extern Coordinates Find_Right_Element();

    extern signed long long Min(signed long long a, signed long long b);

    extern signed long long Max(signed long long a, signed long long b);

    extern void ClearScreen();

    extern void Render_Frame();

    extern void Update_Max_Width_And_Height();

    extern Coordinates Get_Terminal_Content_Size();

    void Update_Frame();
    //Is called on every cycle.
    extern void Query_Inputs();

    extern void MOUSE_API();

    extern void Init_Platform_Stuff();

    extern int Get_Unicode_Length(char first_char);

    extern int Get_Max_Width();

    extern int Get_Max_Height();

    //Returns a char if given ASCII, or a short if given UNICODE
    extern GGUI::UTF* Get(GGUI::Coordinates Abselute_Position);

    extern std::string Liquify_UTF_Text(std::vector<GGUI::UTF> Text, int Width, int Height);

    extern void Update_Frame();
    
    extern void Pause_Renderer();

    extern void Resume_Renderer();

    extern void Recall_Memories();

    extern bool Is(unsigned long long f, unsigned long long Flag);

    extern void Un_Focus_Element();

    extern void Un_Hover_Element();

    extern void Update_Focused_Element(GGUI::Element* new_candidate);

    extern void Update_Hovered_Element(GGUI::Element* new_candidate);

    extern void Event_Handler();

    extern int Get_Free_Class_ID(std::string n);

    extern void Add_Class(std::string name, std::map<std::string, VALUE*> Styling);

    extern void Init_Classes();

    //Inits GGUI and returns the main window.
    extern GGUI::Window* Init_Renderer();

    extern void Report(std::string Problem);

    extern void Nest_UTF_Text(GGUI::Element* Parent, GGUI::Element* child, std::vector<GGUI::UTF> Text, std::vector<GGUI::UTF>& Parent_Buffer);

    extern void Pause_Renderer(std::function<void()> f);

    // Use this to access GGUI.
    extern void GGUI(std::function<void()> DOM, unsigned long long Sleep_For = 0);

    extern void Exit();

    // Also handles shift tabs!
    extern void Handle_Tabulator();

    extern void Handle_Escape();

    extern void Render_Outbox();
}

#endif