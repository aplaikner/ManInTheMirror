# Introduction
ManInTheMirror is an **SNMP network scanning tool** written in **C++** using the [**Net-SNMP library**](http://www.net-snmp.org).<br>
The UI is created using [**Qt5**](https://www.qt.io).

# Prerequisites
- `net-snmp`
    - Installation on Arch Linux: `pacman -S net-snmp`
- `qt5-base`
    - Installation on Arch Linux: `pacman -S qt5-base`
  
# Execution
To execute the program run the binary that is packaged in the latest release or build the project yourself.<br>

# Features
- **Scan single IP** with multiple OIDs
- **Scan network range** with multiple OIDs
- Some **default OIDs are already loaded** into the UI
- **Change community string** in the UI
  
# Default settings
- Default community string is `public`
- Requests are sent using `GETNEXT`, so watch out when inputting OIDs




