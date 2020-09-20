/* For compile with MinGW */
ENTRY(WinMainCRTStartup)
/* For cross compile with mingw-w64 on Ubuntu */
ENTRY(_WinMainCRTStartup)
SECTIONS {
  .text : {
    *(.text)
    *(.rdata)
    *(.pdata)
    *(.xdata)
    *(SORT(.rdata$*))
  }
}
