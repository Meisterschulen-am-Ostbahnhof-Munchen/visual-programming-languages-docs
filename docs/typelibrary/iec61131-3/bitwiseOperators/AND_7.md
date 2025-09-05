# AND_7

<img width="400"  alt="AND_7 Funktionsblock" src="https://github.com/user-attachments/assets/9a02ba15-147c-453c-8863-5c788310e656" />


* * * * * * * * * *

## Einleitung
Der AND_7 Funktionsblock führt eine bitweise logische UND-Verknüpfung (AND) auf bis zu sieben Eingangsvariablen durch. Es handelt sich um einen generischen Funktionsblock, der mit verschiedenen Bit-Datentypen (ANY_BIT) arbeiten kann. Der Block ist gemäß der IEC 61131-3 Norm klassifiziert und eignet sich für den Einsatz in Steuerungs- und Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Normal Execution Request): Startet die Ausführung des Funktionsblocks. Wird mit allen sieben Eingangsvariablen (IN1 bis IN7) verknüpft.

### **Ereignis-Ausgänge**
- **CNF** (Execution Confirmation): Signalisiert die erfolgreiche Ausführung und liefert das Ergebnis der UND-Verknüpfung über die Variable OUT.

### **Daten-Eingänge**
- **IN1** (ANY_BIT): Erster Eingang für die UND-Verknüpfung
- **IN2** (ANY_BIT): Zweiter Eingang für die UND-Verknüpfung
- **IN3** (ANY_BIT): Dritter Eingang für die UND-Verknüpfung
- **IN4** (ANY_BIT): Vierter Eingang für die UND-Verknüpfung
- **IN5** (ANY_BIT): Fünfter Eingang für die UND-Verknüpfung
- **IN6** (ANY_BIT): Sechster Eingang für die UND-Verknüpfung
- **IN7** (ANY_BIT): Siebter Eingang für die UND-Verknüpfung

### **Daten-Ausgänge**
- **OUT** (ANY_BIT): Ergebnis der bitweisen UND-Verknüpfung aller Eingangswerte

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der AND_7 Block führt bei jedem REQ-Ereignis eine bitweise UND-Verknüpfung aller aktiven Eingänge (IN1 bis IN7) durch. Das Ergebnis wird an OUT ausgegeben und das CNF-Ereignis ausgelöst. Der Block ist generisch und kann mit verschiedenen Bit-Datentypen (wie BOOL, BYTE, WORD, DWORD, LWORD) arbeiten.

## Technische Besonderheiten
- Unterstützt den generischen Datentyp ANY_BIT
- Implementiert als generischer Funktionsblock (GEN_AND)
- Teil des iec61131::bitwiseOperators-Pakets
- EPL-2.0 Lizenz

## Zustandsübersicht
Der Block hat keine internen Zustände. Bei jedem REQ-Ereignis wird die Operation sofort ausgeführt und das Ergebnis über CNF zurückgemeldet.

## Anwendungsszenarien
- Bitweise Maskenoperationen in Steuerungsanwendungen
- Logische Verknüpfung mehrerer digitaler Signale
- Signalverarbeitung in Automatisierungssystemen
- Generische Logikoperationen in IEC 61131-3 kompatiblen Systemen

## Vergleich mit ähnlichen Bausteinen
- Standard AND-Blöcke bieten typischerweise nur 2-4 Eingänge
- AND_7 ermöglicht die Verarbeitung von bis zu sieben Eingängen in einer Operation
- Durch die generische Implementierung flexibler als typenspezifische Blöcke

## Fazit
Der AND_7 Funktionsblock bietet eine erweiterte UND-Verknüpfungsfunktionalität für Systeme, die die Verarbeitung mehrerer Eingangssignale in einer einzigen Operation erfordern. Seine generische Natur und IEC 61131-3 Kompatibilität machen ihn zu einem vielseitigen Werkzeug für Automatisierungsanwendungen.
