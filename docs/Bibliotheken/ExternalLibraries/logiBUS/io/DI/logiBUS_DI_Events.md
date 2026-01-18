# logiBUS_DI_Events

```{index} single: logiBUS_DI_Events
```

* * * * * * * * * *

## Einleitung

Die GlobalConstants-Definition `logiBUS_DI_Events` stellt eine umfassende Sammlung von Ereigniskonstanten für digitale Eingänge (DI) im logiBUS-System bereit. Diese Konstanten definieren verschiedene Tastendruck-Ereignisse und deren eindeutige Identifikatoren, die in der Steuerungslogik für die Verarbeitung von Benutzereingaben über Taster verwendet werden.


## Funktionsweise

Die GlobalConstants-Definition `logiBUS_DI_Events` enthält 14 verschiedene Ereigniskonstanten vom Typ `logiBUS_DI_Events_S`, die jeweils durch einen eindeutigen numerischen Wert (`EType`) identifiziert werden. Diese Konstanten werden verwendet, um verschiedene Zustände und Ereignisse von Tastern in der Steuerungslogik zu repräsentieren.

## Technische Besonderheiten

- **Strukturtyp**: Alle Konstanten verwenden den Datentyp `logiBUS_DI_Events_S`
- **Wertebereich**: Die EType-Werte reichen von 0-12 für gültige Ereignisse, mit 255 für ungültige Ereignisse
- **Package-Zugehörigkeit**: `logiBUS::io::DI`
- **Konstantendefinition**: Alle Werte sind als globale Konstanten (CONSTANT) deklariert

Doku zu den einzelnen Events: <https://components.espressif.com/components/espressif/button>

## Zustandsübersicht

Die Ereigniskonstanten decken folgende Zustände ab:

| EType | Konstante | Beschreibung |
|-------|-----------|--------------|
| 0 | BUTTON_PRESS_DOWN | Taster gedrückt |
| 1 | BUTTON_PRESS_UP | Taster losgelassen |
| 2 | BUTTON_PRESS_REPEAT | Taster wiederholt gedrückt |
| 3 | BUTTON_PRESS_REPEAT_DONE | Taster-Wiederholung beendet |
| 4 | BUTTON_SINGLE_CLICK | Einfacher Tastenklick |
| 5 | BUTTON_DOUBLE_CLICK | Doppelklick |
| 6 | BUTTON_MULTIPLE_CLICK | Mehrfachklick |
| 7 | BUTTON_LONG_PRESS_START | Langer Tastendruck beginnt |
| 8 | BUTTON_LONG_PRESS_HOLD | Langer Tastendruck wird gehalten |
| 9 | BUTTON_LONG_PRESS_UP | Langer Tastendruck beendet |
| 10 | BUTTON_PRESS_END | Tastendruck beendet |
| 11 | BUTTON_EVENT_MAX | Maximale Ereignis-ID |
| 12 | BUTTON_NONE_PRESS | Kein Tastendruck |
| 255 | Invalid | Ungültiges Ereignis |

## Anwendungsszenarien

- **Benutzerinterface-Steuerung**: Verarbeitung von Tasteneingaben an Bedienpanels
- **Maschinensteuerung**: Erfassung von manuellen Eingaben an industriellen Steuerungen
- **Sicherheitssysteme**: Überwachung von Not-Aus-Tastern und Sicherheitsschaltern
- **Menünavigation**: Steuerung von Display-Menüs durch Tastereingaben
- **Zustandsüberwachung**: Erkennung verschiedener Tasterbetätigungsmuster

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu einfachen digitalen Eingangsbausteinen, die nur binäre Zustände (EIN/AUS) erfassen, bietet `logiBUS_DI_Events` eine erweiterte Ereigniserkennung mit:
- Zeitlich aufgelösten Ereignissen (Press/Release)
- Komplexen Interaktionsmustern (Klicks, Doppelklicks)
- Langzeit-Erkennung (Long Press)
- Wiederholungsfunktionalität

## Fazit

Die `logiBUS_DI_Events` GlobalConstants-Definition stellt eine umfassende und strukturierte Basis für die Verarbeitung von Tasterereignissen in industriellen Steuerungssystemen bereit. Durch die standardisierten Ereigniscodes ermöglicht sie eine konsistente und wartbare Implementierung von Benutzerinteraktionen über digitale Eingänge.
