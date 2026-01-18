# SoftKeyActivationCode

```{index} single: SoftKeyActivationCode
```

* * * * * * * * * *
## Einleitung
SoftKeyActivationCode ist eine Sammlung von globalen Konstanten für die Verarbeitung von SoftKey-Ereignissen in ISOBUS-kompatiblen Systemen. Diese Konstanten definieren verschiedene Aktivierungszustände von SoftKeys auf virtuellen Terminals und werden zur Steuerung von Benutzerinteraktionen in landwirtschaftlichen Maschinen eingesetzt.

## Schnittstellenstruktur
Bei SoftKeyActivationCode handelt es sich um globale Konstanten und nicht um einen Funktionsblock. Daher existieren keine Ereignis- oder Datenschnittstellen im herkömmlichen Sinne.

### **Konstantendefinitionen**
- **SK_RELEASED**: SoftKey wurde losgelassen (Zustandsänderung) - Code: 0
- **SK_PRESSED**: SoftKey wurde gedrückt (Zustandsänderung) - Code: 1
- **SK_STILL_HELD**: SoftKey wird weiterhin gehalten - Code: 2
- **SK_STILL_HELD_START**: SoftKey wird weiterhin gehalten (Start) - Code: 2, bCyclic: FALSE
- **SK_ABORTED**: SoftKey-Druck wurde abgebrochen (gilt für VT Version 4 und höher) - Code: 3
- **Invalid**: Ungültiger Zustand - Code: 255

## Funktionsweise
Die Konstanten repräsentieren verschiedene Aktivierungszustände von SoftKeys in ISOBUS-Systemen. Sie werden verwendet, um den Status von Benutzerinteraktionen mit virtuellen Terminals zu kennzeichnen. Die Übertragungswiederholrate beträgt bei SoftKey-Druck/Loslassen und alle 200 ms, wenn ein SoftKey gehalten wird.

## Technische Besonderheiten
- Alle Konstanten sind vom Typ `isobus::UT::io::Softkey::SoftKeyActivationCode_S`
- Die Konstanten sind als globale Konstanten definiert und können systemweit verwendet werden
- Die Abort-Funktionalität (SK_ABORTED) ist nur in Virtual Terminal Version 4 und höher verfügbar
- Die Konstante SK_STILL_HELD_START enthält zusätzlich einen booleschen Parameter `bCyclic`

## Anwendungsszenarien
- Steuerung von Benutzeroberflächen in landwirtschaftlichen Maschinen
- Verarbeitung von Touch-Eingaben auf ISOBUS-kompatiblen Displays
- Implementierung von SoftKey-Interaktionen in Virtual Terminal Applikationen
- Zustandsüberwachung von Benutzereingaben in Echtzeit-Steuerungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken bieten globale Konstanten keine aktive Funktionalität, sondern dienen lediglich der Vereinheitlichung von Zustandswerten. Sie sind vergleichbar mit ENUM-Definitionen in anderen Programmiersprachen.

## Fazit
SoftKeyActivationCode stellt eine standardisierte Sammlung von Konstanten für die SoftKey-Verarbeitung in ISOBUS-Umgebungen bereit. Durch die Verwendung dieser Konstanten wird eine einheitliche und wartbare Implementierung von Benutzerinteraktionen in landwirtschaftlichen Steuerungssystemen ermöglicht.