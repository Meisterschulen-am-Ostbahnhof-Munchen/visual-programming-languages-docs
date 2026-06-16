# AIWS_D_FF_TMIN


![AIWS_D_FF_TMIN](./AIWS_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AIWS_D_FF_TMIN** realisiert einen Daten-Latch (D-Flip-Flop) mit einer minimalen Wartezeit zwischen zwei aufeinanderfolgenden Ausgabeereignissen (Minimum inter-disposal Time). Er wird über Adapter-Schnittstellen (Typ: AIWS, unidirektional) angesprochen, die einen Wert aufnehmen und als gelatchten Wert wieder ausgeben. Die Steuerung erfolgt über das Ereignis des Eingabeadapters (CLK-Flanke), wobei die Ausgabe erst nach Ablauf einer einstellbaren Totzeit (Tmin) erfolgt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Kommentar |
|----------|-----|----------|
| INIT | EInit | Initialisierungsanforderung (mit Tmin-Parameter) |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Kommentar |
|----------|-----|----------|
| INITO | EInit | Initialisierungsbestätigung |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|----------|
| Tmin | TIME | Mindestzeit zwischen zwei Ausgabeereignissen (inter-disposal time) |

### **Daten-Ausgänge**
Keine eigenen Datenausgänge – der gelatchte Wert wird ausschließlich über den Adapter **Q** bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|----------|
| Socket (Eingang) | I | adapter::types::unidirectional::AIWS | Wert, der gelatcht werden soll |
| Plug (Ausgang) | Q | adapter::types::unidirectional::AIWS | Gelatchter Wert |

## Funktionsweise
Der FB verwendet intern den Baustein `E_D_FF_ANY_TMIN` aus der IEC 61499-Bibliothek. Der Ablauf ist wie folgt:

1. Bei **INIT** wird die Mindestzeit `Tmin` übernommen und der Baustein initialisiert (`INITO` bestätigt den erfolgreichen Start).
2. Jedes eingehende Ereignis vom Adapter `I.E1` wird als Taktflanke (CLK) interpretiert.
3. Der Datenwert vom Adapter `I.D1` wird bei jeder CLK-Flanke in das interne Flip-Flop übernommen.
4. Der gelatchte Wert wird auf dem Ausgangsadapter `Q.D1` bereitgestellt.
5. Das zugehörige Ereignis `Q.E1` wird jedoch erst dann gesendet, wenn seit dem letzten EO-Ereignis die Zeit `Tmin` verstrichen ist (inter-disposal time). Damit wird die Ausgaberate begrenzt.

Die Verbindung im FBNetzwerk stellt sicher, dass Ereignisse und Daten korrekt zwischen dem Adapter `I`, dem internen FB und dem Adapter `Q` weitergeleitet werden.

## Technische Besonderheiten
- **Adapterbasierte Ein-/Ausgabe:** Der Baustein verwendet ausschließlich Adapter des Typs `AIWS` (unidirektional) für die Signalverarbeitung. Dies erlaubt eine lose Kopplung und Wiederverwendung der Schnittstellen.
- **Interne Nutzung von `E_D_FF_ANY_TMIN`:** Die eigentliche Latch- und Timerlogik wird durch einen spezialisierten Baustein realisiert, der bereits eine minimale Zeit zwischen zwei EO-Ereignissen sicherstellt.
- **Initialisierung erforderlich:** Der Baustein muss vor der ersten Nutzung mit `INIT` initialisiert werden, dabei wird `Tmin` gesetzt.

## Zustandsübersicht
Der FB besitzt im Wesentlichen zwei Betriebsmodi:
- **Initialisierungsphase:** Nach Empfang von `INIT` wird der interne Timer und das Flip-Flop zurückgesetzt. Nach Abschluss wird `INITO` gesendet.
- **Normalbetrieb:** Nach der Initialisierung wartet der Baustein auf CLK-Ereignisse (`I.E1`). Bei jedem CLK wird der Datenwert gelatcht. Ein EO-Ereignis (`Q.E1`) wird erst dann ausgelöst, wenn die seit dem letzten EO verstrichene Zeit **≥ Tmin** ist. Falls die Bedingung nicht erfüllt ist, wird das EO verzögert.

Eine vollständige Zustandsmaschine ist im internen FB implementiert; der hier beschriebene Baustein bildet diese transparent ab.

## Anwendungsszenarien
- **Sensorwert-Erfassung mit minimaler Wiederholrate:** In der Automatisierung soll ein analoger oder digitaler Messwert in definierten Mindestabständen an eine nachgelagerte Steuerung weitergegeben werden, um Überlastung oder unerwünschte Schaltspiele zu vermeiden.
- **Entprellung von Signalflanken:** Das Latch kann verwendet werden, um einen Eingangswert stabil zu halten, während die Ausgabe durch `Tmin` zeitlich entprellt wird.
- **Datenpuffer mit Zeitsteuerung:** In Kommunikationsprotokollen, bei denen Datenpakete nur mit einer minimalen Pause verschickt werden dürfen.

## Vergleich mit ähnlichen Bausteinen
- **Normales D-Flip-Flop (z. B. `E_D_FF`):** Ein Standard-D-FF übernimmt den Eingang bei jeder CLK-Flanke und gibt sofort ein Ereignis aus. Es fehlt die zeitliche Begrenzung der Ausgaberate.
- **`AIWS_D_FF_TMIN`:** Erweitert das einfache D-FF um eine konfigurierbare Mindestzeit zwischen Ausgabeereignissen. Dadurch eignet er sich besonders für zeitkritische und ratebegrenzte Anwendungen.
- **Timer-basierte Latch-Bausteine (z. B. `E_D_FF_ANY_TMIN`):** Der hier verwendete interne FB ist die eigentliche Realisierung; `AIWS_D_FF_TMIN` kapselt diesen in eine adapterbasierte Schnittstelle und erleichtert so die Einbindung in eine IEC 61499-Architektur.

## Fazit
Der Funktionsblock `AIWS_D_FF_TMIN` kombiniert die Funktion eines Daten-Latches mit einer programmierbaren minimalen Ausgabeverzögerung. Durch die adapterbasierte Schnittstellendefinition ist er flexibel in verteilten Automatisierungssystemen einsetzbar. Insbesondere für Anwendungen, bei denen Signalwechsel nur in bestimmten Zeitabständen erfolgen dürfen, bietet er eine einfache und robuste Lösung.