# F_LOG

```{index} single: F_LOG
```

![F_LOG](https://user-images.githubusercontent.com/116869307/214145111-55825954-a2a0-4f08-91b0-7e3e30337b48.png)

* * * * * * * * * *

## Einleitung
Der F_LOG Funktionsblock berechnet den Logarithmus zur Basis 10 (dekadischer Logarithmus) eines numerischen Eingangswerts. Er gehört zur Kategorie der Standardfunktionen für eine numerische Variable gemäß IEC 61131-3 und ist Teil des Pakets `iec61131::numerical`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Berechnung des Logarithmus aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN**: Numerischer Eingangswert vom Typ ANY_REAL, für den der Logarithmus berechnet werden soll

### **Daten-Ausgänge**
- **OUT**: Berechneter Logarithmus-Wert vom Typ ANY_REAL

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Eintreffen eines REQ-Ereignisses berechnet der F_LOG-Block den dekadischen Logarithmus (log₁₀) des aktuellen IN-Werts. Das Ergebnis wird am OUT-Ausgang ausgegeben und gleichzeitig wird ein CNF-Ereignis generiert, um die erfolgreiche Berechnung zu signalisieren.

## Technische Besonderheiten
- Unterstützt den ANY_REAL-Datentyp, was verschiedene numerische Datentypen wie REAL, LREAL etc. ermöglicht
- Einhaltung der IEC 61131-3 Standard-Spezifikation
- Einfache und deterministische Funktionsweise ohne interne Zustände

## Zustandsübersicht
Der Funktionsblock besitzt keine komplexen internen Zustände. Er verhält sich rein funktional: Bei REQ-Ereignis → Berechnung → CNF-Ereignis.

## Anwendungsszenarien
- Wissenschaftliche Berechnungen und Messwertverarbeitung
- Signalverarbeitung in der Automatisierungstechnik
- Skalierung von Messwerten in logarithmischen Darstellungen
- Audio- und Akustik-Anwendungen (z.B. dB-Berechnungen)

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen logarithmischen Funktionen:
- F_LN: Berechnet den natürlichen Logarithmus (Basis e)
- F_LOG: Berechnet spezifisch den dekadischen Logarithmus (Basis 10)
- Beide Blöcke folgen demselben Ereignis-/Datenfluss-Paradigma

## Fazit
Der F_LOG Funktionsblock bietet eine standardisierte, zuverlässige Implementierung für die Berechnung des dekadischen Logarithmus in 4diac-Steuerungssystemen. Seine einfache Schnittstelle und deterministische Funktionsweise machen ihn ideal für den Einsatz in Echtzeit-Automatisierungsanwendungen.
