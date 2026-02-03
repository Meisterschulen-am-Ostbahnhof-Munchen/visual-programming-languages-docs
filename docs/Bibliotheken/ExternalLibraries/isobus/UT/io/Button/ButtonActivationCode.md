# ButtonActivationCode

```{index} single: ButtonActivationCode
```

* * * * * * * * * *
## Einleitung
ButtonActivationCode ist eine Sammlung von globalen Konstanten für die Verarbeitung von Tastenaktivierungen in ISOBUS-kompatiblen Systemen. Diese Konstanten definieren verschiedene Zustände und Ereignisse, die bei der Bedienung von Tasten auftreten können, und werden hauptsächlich in landwirtschaftlichen Anwendungen eingesetzt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*Keine Ereignis-Eingänge vorhanden*

### **Ereignis-Ausgänge**
*Keine Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**
*Keine Daten-Eingänge vorhanden*

### **Daten-Ausgänge**
*Keine Daten-Ausgänge vorhanden*

### **Adapter**
*Keine Adapter vorhanden*

## Funktionsweise
Die ButtonActivationCode-Konstanten definieren verschiedene Tastenaktivierungszustände als strukturierte Datentypen vom Typ `ButtonActivationCode_S`. Jede Konstante repräsentiert einen spezifischen Zustand einer Taste und enthält einen numerischen Code sowie optionale zusätzliche Parameter.

## Technische Besonderheiten
- **Übertragungswiederholungsrate**: Bei Tastendruck/-freigabe und alle 200 ms, wenn die Taste gehalten wird
- **Verriegelbare Tasten**: Wiederholen sich nicht bei gedrückt gehaltener Taste
- **ISOBUS-Kompatibilität**: Speziell für ISOBUS Virtual Terminal (VT) Systeme entwickelt
- **Strukturierte Konstanten**: Verwendung eines strukturierten Datentyps mit Code-Werten und zusätzlichen Flags

## Zustandsübersicht
| Konstante | Code | Beschreibung |
|-----------|------|--------------|
| BT_RELEASED_UNLATCHED | 0 | Taste wurde entriegelt oder losgelassen (Zustandsänderung) |
| BT_PRESSED_LATCHED | 1 | Taste wurde "gedrückt" oder verriegelt (Zustandsänderung) |
| BT_STILL_HELD | 2 | Taste wird weiterhin gehalten (verriegelbare Tasten wiederholen sich nicht) |
| BT_STILL_HELD_START | 2 | Taste wird weiterhin gehalten (mit bCyclic := FALSE) |
| BT_ABORTED | 3 | Tastendruck abgebrochen (gilt für VT Version 4 und höher) |
| Invalid | 255 | Ungültiger Zustand |

## Anwendungsszenarien
- Steuerung von landwirtschaftlichen Maschinen über ISOBUS Virtual Terminal
- Implementierung von Tastenlogik in Bedienpanels
- Verarbeitung von Tasteneingaben in Fahrzeugsteuerungssystemen
- Entwicklung von Benutzerschnittstellen für landwirtschaftliche Anwendungen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingängen bietet ButtonActivationCode eine fein granulierte Zustandsdarstellung für Tasten, die speziell auf die Anforderungen von ISOBUS-Systemen zugeschnitten ist. Die Konstanten unterstützen erweiterte Tastenfunktionen wie Verriegelungsmechanismen und Abbruchfunktionen.

## Fazit
ButtonActivationCode bietet eine standardisierte Methode zur Behandlung von Tastenaktivierungen in ISOBUS-Umgebungen. Durch die definierten Konstanten wird eine konsistente und zuverlässige Verarbeitung von Tasteneingaben über verschiedene Systeme hinweg ermöglicht, was besonders in sicherheitskritischen landwirtschaftlichen Anwendungen von Bedeutung ist.