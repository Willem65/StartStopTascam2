//  
//  Control/Preset/Sense Command < 80h
//  Return Command > 80h
//
//  OF INFORMATION REQUEST
//  8F INFORMATION RETURN

//  10 STOP
//  12 PLAY
//  13 RECORD
//  14 READY
//  16 SHUTTLE
//  18 TRAY/EJECT
//  1A TRACK/INDEX SKIP 
//
//  20 AUTO CUE LEVEL PRESET
//  A0 AUTO CUE LEVEL RETURN
//  
//  21 AUTO TRACK LEVEL PRESET  
//  A1 AUTO TRACK LEVEL RETURN
//  
//  23 DIRECT TRACK SEARCH PRESET  
//
//  25 PTTCH DATA PRESET
//  A5 PITCH DATA RETURN
//  
//  28 SYNC REC LEVEL PRESET  
//  A8 SYNC REC LEVEL RETURN
//  
//  29 TITLE PRESET  
//  A9 TITLE PRESET ACKNOWUEDGE RETURN
//  
//  2C TIME SEARCH PRESET
//
//  2D KEY CONTROL DATA PRESET  
//  AD KEY CONTROL DATA RETURN
//  
//  2F DIGITAL VOLUME DATA PRESET
//  AF DIGITAL VOLUE DATA RETURN
//  
//  30 AUTO CUE SELECT
//  B0 AUTO CUE SELECT RETURN
//  
//  31 AUTO TRACK SELECT
//  B1 AUTO TRACK RETURN
//  
//  32 EOM TRAO< TIME SELECT
//  B2 EOM TRACK TIME RETURN
//  
//  33 EOM DISC TIME SELECT
//  B3 EOM DISCTIME RETURN
//  
//  34 RESUME/TIMER PLAY SELECT
//  B4 RESUME/TIMER PLAY SELECT RETURN
//  
//  35 PITCH CONTROL SELECT
//  B5 PITCH CONTROL SELECT RETURN
//  
//  36 AUTO READY SELECT
//  B6 AUTO READY SEUECT RETURN
//  
//  37 REPEAT SELECT
//  B7 REPEAT SEIECT RETURN
//  
//  38 SYNC REC SELECT
//  B8 SYNC REC SELECT RETURN
//  
//  3D KEY CONTROL SELECT
//  BD KEY CONTROL SELECT RETURN
//  
//  4C REMOTE/LOCAL SELECT
//  CC REMOTE/LOCAL SELECT RETURN
//  
//  4E PLAY MODE SENSE
//  CE PLAY MODE RETURN
//  
//  50 MECHA STATUS SENSE  
//  D0 MECHA STATUS RETURN
//  
//  55 TRACK No. STATUS SENSE
//  D5 TRACK No. STATUS RETURN
//  
//  56 DISC STATUS SENSE
//  D6 DISC STATUS RETURN
//  
//  57 CURRENT TRACK INFORMATIO SENSE
//  D7 CURRENT TRACK INFORMATION RETURN
//  
//  58 CURRENT TRACK TIME SENSE
//  D8 CURRENT TRACK TIME RETLRN
//  
//  59 TTTLE SENSE
//  D9 TITIE RETURN
//  
//  5D TOTAL TRACK No TTOTAL TIME SENSE
//  DD TOTAL TRACK No./TOTAL TIME RETURN
//  
//  5E PGM TOTAL TRACK No./TOTAL TIM SENSE
//  DE PGM TOTAL TRACK No./TOTAL TIME RETURN
//  
//  5F KEYBOARD TYPE SENSE
//  DF KEYBOARD TYPE RETURN
//  
//  F0 ERROR SENSE REQUEST RETURN
//  
//  F1 CAUTION SENSE REQUEST RETURN
//  
//  F2 ILLEGAL STATUS RETURN
//  
//  F4 POWER ON STATUS RETURN
//  
//  F6 CHANGE STATUS RETURN
//  
//  78 ERROR SENSE
//  F8 ERROR SENSE RETURN
//
//  79 CAUTION SENSE
//  F9 CAUTION SENSE RETURN
//  
//  
//  
//  
//  	  
//  
//  TASCAM MD-CD1 RS-232C Protocol Specifications
//  
//  3. Command Format
//  
//  3.1. Overview of Command Format
//  The command format is as follows:
//  
//  Byte1     Byte2       Byte 3  Byte 4       Byte 5    Byte 6      Byte 7      Byte 8   ...   Byte-n
//   LF         ID           Command           Data 1    Data 2      Data 3      Data 4   ...   CR
//  
//  A command is based on ASCII format, starting from ???Line feed (LF)??? and ending with ???Carriage return
//  (CR)-"
//  Next byte of LF is a machine ID. Machine ID is described later.
//  A command is represented with ASCII 2 bytes.
//  A series of bytes following the command represents data, O byte (no data) or more up to 98 bytes. For
//  detail of data, refer to the detail of each command. For a command which uses 0-9 and A-F for data value,
//  upper cases of A-F are used.
//  
//  A sample command:
//  Sample 1: 
//  To send PLAY command to the controlled device with lD=1.
//  This command starts the controlled device to play when is stopped or ready.
//  PLAY command is [12], and sent as follows:
//  
//                       ID        Command  
//  ASClI     LF         1         1       2        CR
//  HEX      0x0Ah    0x31      0x31    0x32       0x0D
//  
//  Sample 2:
//  To order the controlled device with lD=1 to perform direct search to 123rd track.
//  In order to perform this operation, send the command ???DIRECT TRACK SEARCH PRESET
//  [23]."
//  The data bytes are composed of 2-byte unit ASCII characters.
//  Specification of Track No. in ???DIRECT TRACK SEARCH PRESET??? command is as follows:
//  Data 1 Number at ten's place of the track number to be specified.
//  Data 2 Number at unit???s place of the track number to be specified.
//  Data 3 Number at thousand's place of the track number to be specified.
//  Data 4 Number at hundred???s place of the track number to be specified.
//  Then, the command to be sent is as follows:
//  
//        ID Command Data: 123rd track
//  LF       2      2     3      2      3     0      1     CR
//  OAh     32h    32h   33h    32h    33h   30h    31h    ODh
//  
//  Sample 3:
//  To write a title into 123rd track of the controlled device with lD=2.
//  In order to perform this operation, send the command ???TITLE PRESET [29]."
//  Using this command, up to 96 characters can be sent.
//  For example, the command to be sent to write a title ???Test??? is as follows:
//  
//       ID      Command     123 rd track         Title: Test
//  LF   2        2   9      2   3   O   1         T e s t             CR
//  OAh 32h      32h 39h     32h 33h 30h 31h      54h 65h 73h 74h      ODh
//  
//  3.2. Machine ID
//  For this device, Machine ID=1 for commands and returns on MD
//  and Machine ID=2 for commands and
//  returns on CD are assigned.
//  Commands and returns with Machine ID=0 exist, and theses operations are described in context.
//  If a command with Machine ID=3 or more is received, it is ignored.
//  If a command with illegal Machine ID is received (MD receives a command with CD???s ID, or other cases),
//  this device sends ILLEGAL [F2].

//---------------------------------------------------------------------------------------------------------------

#include <Arduino.h>
#include <SoftwareSerial.h>

// Set up a new SoftwareSerial object with RX in digital pin 10 and TX in digital pin 11
//SoftwareSerial mySerial(10, 11);

SoftwareSerial mySerial(4, 3);

unsigned int PIN_MD = 16;
unsigned int PIN_CD = 14;
unsigned int PIN_LED = 2;
unsigned int debounce = 50;

// functions
#define FN_PLAY_CD   0
#define FN_STOP_CD   1
#define FN_PLAY_MD   2
#define FN_STOP_MD   3

#define BEGIN     0x0A
#define END       0x0D

#define ID_CD     0x32
#define ID_MD     0x31

#define CMD_STOP  "10"
#define CMD_PLAY  "12"

int PIN_MD_Prev = 0;
int PIN_CD_Prev = 0;
int PIN_MD_Curr = 0;
int PIN_CD_Curr = 0;

struct CMD_STRUCT 
{
  unsigned char id;
  unsigned char cmd[2];
};

// global variable
struct CMD_STRUCT cmds[4] = {
  {ID_CD, CMD_PLAY[0], CMD_PLAY[1]},  // FN_PLAY_CD
  {ID_CD, CMD_STOP[0], CMD_STOP[1]},  // FN_STOP_CD
  {ID_MD, CMD_PLAY[0], CMD_PLAY[1]},  // FN_PLAY_MD
  {ID_MD, CMD_STOP[0], CMD_STOP[1]}   // FN_STOP_MD
};


void setup() {
    pinMode(PIN_MD, INPUT);
    digitalWrite(PIN_MD, HIGH);       
    pinMode(PIN_CD, INPUT);
    digitalWrite(PIN_CD, HIGH);
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH);           
    mySerial.begin(9600);    
}

void do_function( int functionNr )
{
    struct CMD_STRUCT fn = cmds[functionNr];
    unsigned char tmp;
    
    // begin
    tmp = BEGIN;
    mySerial.write(&tmp, 1);
    // send id
    mySerial.write(&fn.id, 1);
    // send cmd
    mySerial.write(fn.cmd, 2);
    // end
    tmp = END;
    mySerial.write(&tmp, 1);
}

void loop() 
{    
    // Handle CD Player
    PIN_CD_Curr = digitalRead(PIN_CD);

    if (PIN_CD_Curr != PIN_CD_Prev) {
        if (PIN_CD_Curr) {
            // pin high
            do_function( FN_STOP_CD );
            digitalWrite(PIN_LED, HIGH);
        }else {
            // pin low
            do_function( FN_PLAY_CD );
            digitalWrite(PIN_LED, LOW);
        }
        PIN_CD_Prev = PIN_CD_Curr;
    }
    

    // Handle MD Player
    PIN_MD_Curr = digitalRead(PIN_MD);

    if (PIN_MD_Curr != PIN_MD_Prev) {
        if (PIN_MD_Curr) {
            // pin high
            digitalWrite(PIN_LED, HIGH);
            do_function( FN_STOP_MD );
        }else {
            // pin low
            do_function( FN_PLAY_MD );
            digitalWrite(PIN_LED, LOW);
        }
        PIN_MD_Prev = PIN_MD_Curr;
    }

    delay(debounce);     
}
