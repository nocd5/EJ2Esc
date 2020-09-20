ENTRY(WinMainCRTStartup)
/* For cross compile on WSL */
/* ENTRY(_WinMainCRTStartup) */
SECTIONS {
  .text : {
    *(.text)
    *(.rdata)
    *(.pdata)
    *(.xdata)
    *(SORT(.rdata$*))
  }
}
