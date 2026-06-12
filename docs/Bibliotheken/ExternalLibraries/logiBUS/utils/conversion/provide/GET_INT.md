# GET_INT


![GET_INT](./GET_INT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **GET_INT** dient dazu, den aktuellen Wert einer INT-Variablen (als InOut-Parameter definiert) auszulesen und als gepufferten Wert am Ausgang bereitzustellen. Die Pufferung erfolgt bei jedem Ausführungszyklus, sodass der Ausgangswert bis zur nächsten Anforderung stabil bleibt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Beschreibung |
|----------|--------------|
| **REQ** | Normaler Ausführungsrequest; löst das Auslesen der InOut-Variablen **IN** aus. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| **CNF** | Bestätigung der Ausführung; signalisiert, dass der Wert von **IN** gepuffert und am Ausgang **OUT** bereitsteht. |

### **Daten-Eingänge**
– *Keine eigenständigen Dateneingänge vorhanden.*

Der Eingabewert wird über den InOut-Parameter **IN** bereitgestellt (siehe nächster Abschnitt).

### **Daten-Ausgänge**
| Ausgang | Typ | Beschreibung |
|---------|-----|--------------|
| **OUT** | INT | Gepufferter Ausgabewert, der den letzten gelesenen Wert von **IN** enthält. Initialwert: 0. |

### **Adapter**
– *Keine Adapter vorhanden.*

### **InOut-Variablen (implizit)**
| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| **IN** | INT | Quelle des auszulesenden Werts. Kann sowohl als Eingabe als auch als Ausgabe verwendet werden (hier nur lesend). Initialwert: 0. |

## Funktionsweise
Der FB arbeitet als einfacher Lesepuffer:
1. Beim Eintreffen des Ereignisses **REQ** wird die **ST**-Algorithmus `REQ` ausgeführt:
   ```structured text
   OUT := IN;
   ```
2. Der aktuelle Wert der InOut-Variablen **IN** wird in den Ausgang **OUT** kopiert.
3. Anschließend wird das Ereignis **CNF** ausgegeben, um den Abschluss der Operation zu signalisieren.

Da **IN** als InOut-Parameter deklariert ist, wird innerhalb des Bausteins direkt auf die Speicherstelle der übergeordneten Applikation zugegriffen. Der Wert wird nicht verändert, sondern lediglich ausgelesen und zwischengespeichert.

## Technische Besonderheiten
- **InOut-Parameter**: Die Verwendung einer InOut-Variable erlaubt den direkten Zugriff auf die Datenquelle ohne separate Daten-Eingänge und -Ausgänge. Dies reduziert die Anzahl der Verbindungen und spart Ressourcen.
- **Pufferung**: Der Ausgang **OUT** behält seinen Wert, bis der nächste **REQ**-Aufruf erfolgt. Dadurch ist der Ausgabewert unabhängig von möglichen Änderungen der Quelle zwischen zwei Lesezyklen.
- **Initialwerte**: Sowohl **IN** als auch **OUT** starten mit 0, sodass auch ohne vorherige Ausführung definierte Werte vorliegen.

## Zustandsübersicht
Der FB besitzt einen einzigen Zustand **REQ**:
- **REQ**: Bei Aktivierung wird der Algorithmus `REQ` ausgeführt, danach das Ereignis **CNF** gesendet. Der Zustand bleibt bestehen (kein Übergang in einen anderen Zustand).

| Zustand | Eintrittsbedingung | Aktion | Ausgangsereignis |
|---------|-------------------|--------|------------------|
| REQ     | Ereignis **REQ** empfangen | `OUT := IN;` | CNF |

## Anwendungsszenarien
- **Datenpufferung**: Ein von mehreren Bausteinen genutzter INT-Wert soll stabil zur Verfügung stehen, ohne dass jeder Baustein direkt auf die Quelle zugreifen muss.
- **Synchronisation**: In zeitkritischen Steuerungen kann der aktuelle Wert einer Variablen zu einem bestimmten Zeitpunkt „eingefroren“ und später verarbeitet werden.
- **Ersatz eines MOVE-FBs**: Wenn aus Performance-Gründen ein direkter Speicherzugriff über InOut bevorzugt wird, ersetzt **GET_INT** den klassischen MOVE-Baustein mit separatem Eingang und Ausgang.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Typ des Eingangs | Pufferung | Besonderheit |
|----------|------------------|-----------|--------------|
| **GET_INT** | InOut (INT) | Ja (einmaliges Lesen bei REQ) | Zugriff auf Originalvariable, keine zusätzliche Variable erforderlich |
| **MOVE** (z.B. IEC 61131-3) | Eingang (INT) | Ja (bei jeder Ausführung) | Kopiert Wert von einem expliziten Eingang in einen Ausgang |
| **F_TRIG / R_TRIG** | Eingang (BOOL) | Nein (nur Flankenerkennung) | Arbeitet mit Booleschen Werten |

Der Hauptunterschied liegt im Verzicht auf einen separaten Dateneingang durch die Nutzung eines InOut-Parameters.

## Fazit
**GET_INT** ist ein einfacher, aber effektiver Funktionsblock zum gepufferten Auslesen einer INT-Variable. Durch die Verwendung eines InOut-Parameters reduziert er den Verbindungsaufwand und eignet sich besonders für Anwendungen, in denen ein stabiler Momentanwert benötigt wird. Seine klare, zustandsarme Struktur macht ihn zuverlässig und leicht verständlich.