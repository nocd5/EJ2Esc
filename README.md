# EJ2Esc

Replace E/J(半角/全角) key to Escape key, and disable CapsLock

## Detals

Replace E/J(半角/全角) key to Escape key using RegisterHotkey API  
except with Alt- modifier key.

Additionally, disable CapsLock using a timer.  
The timer checks CapsLock state per 1 second,
and turns off if it's on.

### Why I make it

Although I want to change keyon  only own user,  
per user setting with a registory key `HKEY_CURRENT_USER\Keyboard Layout`  
is not working on Windows 10

## How to stop

Please kill from Task Manager or using `taskkill` command.

```
taskkill /f /im EJ2Esc.exe
```

