#include "mbed.h"
#include "mbed_rpc.h"
#include "uLCD_4DGL.h"

uLCD_4DGL lcd(p28, p27, p29);
Serial pc(USBTX, USBRX);
void rpcLCD(Arguments *in , Reply *out) {
    const char *str = in->getArg<const char*>();
    lcd.printf("%s", str);
    out->putData(str);
}
RPCFunction uLCD(&rpcLCD, "uLCD");

int main() {
    char buf[256], outbuf[256];
    while(1) {
        pc.gets(buf, 256);
        //Call the static call method on the RPC class
        RPC::call(buf, outbuf); 
        pc.printf("%s\n", outbuf);
    }
}
