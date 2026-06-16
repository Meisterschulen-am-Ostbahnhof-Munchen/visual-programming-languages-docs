# ILOCK_IO_AX


![ILOCK_IO_AX](./ILOCK_IO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ILOCK_IO_AX** realisiert einen kettbaren (chainable) Momentanschalter (Momentary Latch) mit Interlock-Funktion. Er stellt sicher, dass immer nur ein Element in einer Kette aktiv ist – sobald ein anderer FB in der Kette aktiv wird, wird dieser zurückgesetzt. Der FB ist speziell für die Verwendung mit AX/AX2-Adapterschnittstellen ausgelegt.

## Schnittstellenstruktur
Der Baustein besitzt keine klassischen Ereignis- oder Datenein-/ausgänge auf FB-Ebene. Die gesamte Kommunikation erfolgt über **Adapter-Schnittstellen**. Nachfolgend sind die über die Adapter übertragenen Signale aufgeschlüsselt.

### **Ereignis-Eingänge**

| Signal | Adapter | Beschreibung |
|--------|---------|--------------|
| `IN.E1` | IN (AX) | Auslöser für die Verarbeitung des Eingangssignals. |
| `ILOCK_IN.EO1` | ILOCK_IN (AX2) | Ereignis vom übergeordneten FB in der Kette (z. B. wenn dort ein anderer Ausgang aktiv wird). |
| `ILOCK_OUT.EI1` | ILOCK_OUT (AX2) | Ereignis vom untergeordneten FB in der Kette (z. B. wenn dieser aktiv wird). |

### **Ereignis-Ausgänge**

| Signal | Adapter | Beschreibung |
|--------|---------|--------------|
| `OUT.E1` | OUT (AX) | Bestätigung, dass die Verarbeitung abgeschlossen ist. |
| `ILOCK_IN.EI1` | ILOCK_IN (AX2) | Ereignis an den übergeordneten FB (wird bei jedem Verarbeitungszyklus gesendet). |
| `ILOCK_OUT.EO1` | ILOCK_OUT (AX2) | Ereignis an den untergeordneten FB (wird bei jedem Verarbeitungszyklus gesendet). |

### **Daten-Eingänge**

| Signal | Adapter | Beschreibung |
|--------|---------|--------------|
| `IN.D1` | IN (AX) | Setzeingang (BOOL) – wenn TRUE und kein anderer FB in der Kette aktiv, wird der Ausgang aktiv. |
| `ILOCK_IN.DO1` | ILOCK_IN (AX2) | Zustand des übergeordneten FBs (TRUE bedeutet, dass dort der Ausgang aktiv ist). |
| `ILOCK_OUT.DI1` | ILOCK_OUT (AX2) | Zustand des untergeordneten FBs (TRUE bedeutet, dass dort der Ausgang aktiv ist). |

### **Daten-Ausgänge**

| Signal | Adapter | Beschreibung |
|--------|---------|--------------|
| `OUT.D1` | OUT (AX) | Ausgangssignal (BOOL) – aktiv, wenn `IN.D1` gesetzt und kein anderer FB in der Kette aktiv ist. |
| `ILOCK_IN.DI1` | ILOCK_IN (AX2) | Eigenes Ausgangssignal wird an den übergeordneten FB weitergegeben. |
| `ILOCK_OUT.DO1` | ILOCK_OUT (AX2) | Eigenes Ausgangssignal wird an den untergeordneten FB weitergegeben. |

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `IN` | Socket (Eingang) | `adapter::types::unidirectional::AX` | Eingangssignal vom Anwender (Setzeingang und Ereignis). |
| `OUT` | Plug (Ausgang) | `adapter::types::unidirectional::AX` | Ausgangssignal zum Anwender (Ausgangswert und Bestätigung). |
| `ILOCK_IN` | Socket (Eingang) | `adapter::types::bidirectional::AX2` | Verbindung zum **übergeordneten** FB in der Kette. |
| `ILOCK_OUT` | Plug (Ausgang) | `adapter::types::bidirectional::AX2` | Verbindung zum **untergeordneten** FB in der Kette. |

## Funktionsweise
Der FB arbeitet als **Momentanschalter mit Interlock** (auch „exklusiver Latch“). Im Zustand `REQ` wird folgende Logik ausgeführt:
- Der Ausgang `OUT.D1` wird nur dann **TRUE**, wenn der Eingang `IN.D1` aktiv ist **und** kein anderer FB in der Kette gerade aktiv ist (`ILOCK_IN.DO1` vom Vorgänger und `ILOCK_OUT.DI1` vom Nachfolger müssen FALSE sein).
- Der eigene aktive Zustand (`OUT.D1`) wird über die Adapter `ILOCK_IN.DI1` (an den Vorgänger) und `ILOCK_OUT.DO1` (an den Nachfolger) weitergegeben.
- Jeder auslösende Ereigniseingang (egal ob von `IN.E1`, `ILOCK_IN.EO1` oder `ILOCK_OUT.EI1`) führt zur erneuten Berechnung der Logik und zur Ausgabe aller Ereignisse (`OUT.E1`, `ILOCK_IN.EI1`, `ILOCK_OUT.EO1`).

Durch die bidirektionale Weitergabe des Zustands über die ILOCK-Adapter wissen alle FBs in der Kette voneinander, sodass nur einer aktiv sein kann.

## Technische Besonderheiten
- **Kettbare Interlock-Struktur**: Mehrere ILOCK_IO_AX-Bausteine können hintereinander geschaltet werden, indem `ILOCK_OUT` eines FBs mit `ILOCK_IN` des nächsten verbunden wird. Die Kette kann beliebig lang sein.
- **Keine eigenen Ereignisse/Daten auf FB-Ebene**: Die gesamte Signalübertragung erfolgt über die standardisierten AX/AX2-Adapter. Dies ermöglicht eine einfache Integration in bestehende Adapter-basierte Systeme.
- **Immer nur eine Verarbeitung**: Da nur ein Zustand (`REQ`) existiert, wird bei jedem Ereignis dieselbe Logik ausgeführt. Es gibt keine internen Zustandswechsel.

## Zustandsübersicht
Der FB besitzt nur einen einzigen Zustand:

```
+-------+
|  REQ  |  (Standardzustand)
+-------+
    | ^
    | | (Ereignisse: IN.E1, ILOCK_IN.EO1, ILOCK_OUT.EI1)
    +-+
```

Im Zustand `REQ` werden die Algorithmus `REQ` und die Ereignisausgaben ausgeführt. Der Zustand wird nie verlassen.

## Anwendungsszenarien
- **Steuerung von Schaltgeräten** (z. B. Ventile, Motoren) in einer Linie, bei der immer nur eines aktiv sein darf.
- **Prioritätslose Auswahl** aus mehreren Quellen (z. B. Tasterfeld mit Interlock).
- **Verkettete Sicherheitssteuerungen**, bei denen eine Aktivierung einer nachfolgenden Stufe die vorherige deaktivieren muss (oder umgekehrt).

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung | Unterschied zu ILOCK_IO_AX |
|----------|--------------|----------------------------|
| **SR-Flipflop** | Setzt Ausgang bei SET, rückgesetzt bei RESET. | Kein Interlock – mehrere FBs können gleichzeitig aktiv sein. |
| **Einfacher Latch (z. B. LATCH_AX)** | Hält Wert solange, bis erneut getriggert. | Keine Kopplung mit anderen FBs. |
| **ILOCK_IO_AX** | Exklusive Aktivierung in einer Kette. | Erzwingt, dass nur ein FB aktiv ist – ideal für Liniensteuerungen. |

## Fazit
Der **ILOCK_IO_AX** ist ein spezialisierter Funktionsblock für exklusive Aktivierungen in geketteten Anordnungen. Durch die Verwendung von AX/AX2-Adaptern und die bidirektionale Zustandsrückmeldung wird eine robuste Interlock-Logik ohne separate Verdrahtung realisiert. Er eignet sich besonders für modulare Steuerungsstrukturen, bei denen mehrere Aktoren nur nacheinander oder einzeln aktiv sein dürfen.