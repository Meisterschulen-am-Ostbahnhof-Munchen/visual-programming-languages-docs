# OR_9

<img width="1109" height="384" alt="OR_9" src="https://github.com/user-attachments/assets/32910d98-c116-4a57-b0e3-bcb3ac9241a5" />

* * * * * * * * * *
## Einleitung
Der OR_9 Funktionsblock ist ein generischer Baustein zur Berechnung einer bitweisen logischen ODER-Verknüpfung. Er unterstützt bis zu neun Eingangsvariablen und gibt das Ergebnis der ODER-Operation aus. Der Baustein ist Teil der IEC 61131-3 Standardbibliothek für bitweise boolesche Funktionen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderungseingang. Löst die Berechnung der ODER-Verknüpfung aus. Verknüpft mit allen Daten-Eingängen (IN1 bis IN9).

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach der Berechnung der ODER-Verknüpfung ausgelöst. Verknüpft mit dem Daten-Ausgang OUT.

### **Daten-Eingänge**
- **IN1** (ANY_BIT): ODER-Eingang 1
- **IN2** (ANY_BIT): ODER-Eingang 2
- **IN3** (ANY_BIT): ODER-Eingang 3
- **IN4** (ANY_BIT): ODER-Eingang 4
- **IN5** (ANY_BIT): ODER-Eingang 5
- **IN6** (ANY_BIT): ODER-Eingang 6
- **IN7** (ANY_BIT): ODER-Eingang 7
- **IN8** (ANY_BIT): ODER-Eingang 8
- **IN9** (ANY_BIT): ODER-Eingang 9

### **Daten-Ausgänge**
- **OUT** (ANY_BIT): Ergebnis der ODER-Verknüpfung aller Eingänge

### **Adapter**
Der Baustein verfügt über keine Adapter.

## Funktionsweise
Der OR_9 Funktionsblock führt eine bitweise logische ODER-Verknüpfung aller aktiven Eingänge (IN1 bis IN9) durch, wenn das REQ-Ereignis empfangen wird. Das Ergebnis wird am OUT-Ausgang ausgegeben und gleichzeitig das CNF-Ereignis ausgelöst.

## Technische Besonderheiten
- Unterstützt den generischen Datentyp ANY_BIT für alle Eingänge und den Ausgang
- Kann mit verschiedenen Bitlängen (z.B. BYTE, WORD, DWORD) arbeiten
- Implementiert als generischer Baustein (GEN_OR)

## Zustandsübersicht
1. Wartezustand: Auf REQ-Ereignis warten
2. Berechnungszustand: Führt ODER-Verknüpfung durch
3. Ausgabezustand: Setzt OUT und löst CNF aus
4. Rückkehr in Wartezustand

## Anwendungsszenarien
- Bitweise Signalverarbeitung
- Kombinatorische Logikschaltungen
- Steuerungslogik mit mehreren Eingangsbedingungen
- Signalverarbeitung in industriellen Automatisierungssystemen

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfacheren ODER-Bausteinen bietet OR_9 die Möglichkeit, bis zu neun Eingänge zu verarbeiten
- Ähnlich zu anderen bitweisen Operatoren, aber speziell für ODER-Verknüpfungen optimiert
- Generische Implementierung ermöglicht flexiblere Anwendung als typspezifische Varianten

## Fazit
Der OR_9 Funktionsblock ist ein vielseitig einsetzbarer Baustein für bitweise ODER-Verknüpfungen in industriellen Steuerungssystemen. Seine generische Implementierung und Unterstützung für bis zu neun Eingänge machen ihn besonders flexibel für verschiedene Anwendungsfälle. Die klare Schnittstellenstruktur und Standardkonformität nach IEC 61131-3 ermöglichen eine einfache Integration in bestehende Automatisierungslösungen.
