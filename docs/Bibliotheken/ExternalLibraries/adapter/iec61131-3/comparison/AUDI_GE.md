# AUDI_GE


![AUDI_GE](./AUDI_GE.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AUDI_GE` führt einen Vergleich zweier Werte auf „größer oder gleich“ durch. Er stellt das Ergebnis als booleschen Wert bereit. Der Baustein ist als Komposition realisiert und nutzt intern den Standard‑Vergleichsbaustein `F_GE` aus der IEC 61131-3‑Bibliothek. Die Ein‑ und Ausgabe erfolgt ausschließlich über unidirektionale Adapter.

## Schnittstellenstruktur
### **Ereignis‑Eingänge**
- **Keine direkten Ereignisseingänge**  
  Die Auslösung des Vergleichs erfolgt über die **Socket‑Adapter** `IN1` und `IN2`. Jeder dieser Adapter liefert ein Ereignis an den internen Baustein, sobald gültige Daten anliegen.

### **Ereignis‑Ausgänge**
- **Keine direkten Ereignisausgänge**  
  Das Ergebnis des Vergleichs wird über den **Plug‑Adapter** `OUT` als Ereignis weitergereicht, sobald die Auswertung abgeschlossen ist.

### **Daten‑Eingänge**
Die Datenwerte, die verglichen werden sollen, werden über die Adapter bezogen:
- **Adapter `IN1`** – liefert den ersten Vergleichswert (Typ entsprechend dem Adapter `AUDI`).
- **Adapter `IN2`** – liefert den zweiten Vergleichswert (Typ entsprechend dem Adapter `AUDI`).

### **Daten‑Ausgänge**
- **Adapter `OUT`** – gibt den booleschen Wert `TRUE` aus, wenn `IN1 ≥ IN2` ist, andernfalls `FALSE` (Typ entsprechend dem Adapter `AX`).

### **Adapter**
| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `IN1` | Socket | `adapter::types::unidirectional::AUDI` | Erster Eingabewert |
| `IN2` | Socket | `adapter::types::unidirectional::AUDI` | Zweiter Eingabewert |
| `OUT` | Plug | `adapter::types::unidirectional::AX` | Ausgabe: `IN1 >= IN2` (boolesch) |

## Funktionsweise
1. Die Ereignisse von `IN1.E1` und `IN2.E1` werden zum internen `F_GE`‑Baustein geführt (über eine ODER‑Verknüpfung – beide Ereignisse triggern denselben `REQ`‑Eingang).
2. Gleichzeitig werden die Daten `IN1.D1` und `IN2.D1` an die entsprechenden Eingänge `F_GE.IN1` und `F_GE.IN2` übergeben.
3. Der interne Baustein `F_GE` berechnet `IN1 ≥ IN2`.
4. Das Ergebnis erscheint am Ausgang `F_GE.OUT` und wird an den Adapter `OUT.D1` weitergegeben.
5. Mit dem Ereignis `F_GE.CNF` wird `OUT.E1` ausgelöst, um der Umgebung zu signalisieren, dass ein neues Ergebnis vorliegt.

## Technische Besonderheiten
- Der Baustein ist vollständig adapterbasiert – er besitzt keine klassischen Ereignis‑ oder Dateneingänge auf der obersten Ebene.
- Die Adapter `AUDI` und `AX` sind unidirektional und müssen im entsprechenden Projekt definiert sein.
- Die Ausführung erfolgt asynchron: Sobald einer der beiden Eingangsadapter ein Ereignis liefert, wird der Vergleich neu berechnet. Eine Synchronisation der Werte ist nicht erforderlich, da beide Daten gleichzeitig anliegen müssen, damit das Ergebnis sinnvoll ist.
- Die Bausteinkonfiguration entspricht der IEC 61131‑3‑Norm und der Eclipse 4diac‑Umgebung.

## Zustandsübersicht
Der Baustein selbst besitzt keinen expliziten Zustandsautomaten – die gesamte Steuerlogik liegt im internen `F_GE`. Sein Verhalten ist deterministisch:
- **Warten auf Trigger**: Solange kein Ereignis an `IN1` oder `IN2` eintrifft, bleibt der Ausgang `OUT` unverändert.
- **Berechnung**: Bei Eintreffen eines Ereignisses wird der Vergleich ausgeführt.
- **Ergebnisausgabe**: Das Ergebnis wird am Ausgang bereitgestellt und ein Ereignis am `OUT`‑Adapter gesendet.

## Anwendungsszenarien
- **Zustandsüberwachung**: Prüfen, ob ein Messwert einen Schwellwert erreicht oder überschreitet.
- **Aktorsteuerung**: Aktivieren eines Ausgangs, sobald eine Bedingung `Wert1 ≥ Wert2` erfüllt ist.
- **Wertvergleich in Produktionsanlagen**: Vergleichen von Soll‑/Ist‑Werten in kontinuierlichen Prozessen.
- **Einfache logische Verknüpfungen**: Als Bestandteil komplexerer Sicherheits‑ oder Steuerungslogik.

## Vergleich mit ähnlichen Bausteinen
- **AUDI_GT** (greater than) – vergleicht auf `>`, liefert `TRUE` nur bei strikt größerem ersten Wert.
- **AUDI_EQ** (equal) – vergleicht auf Gleichheit.
- **AUDI_LE** (less or equal) – das Gegenstück für `≤`.
- **AUDI_GE** ist der direkte Partner zu `AUDI_LE` und deckt den Fall „mindestens gleich“ ab. Im Vergleich zu einem Einzelbaustein wie `F_GE` bietet `AUDI_GE` eine adapterbasierte Kapselung, was die Wiederverwendung in verschiedenen Projekten erleichtert.

## Fazit
`AUDI_GE` ist ein spezialisierter Vergleichsbaustein, der durch die Verwendung von Adaptern eine flexible und saubere Schnittstellendefinition ermöglicht. Er eignet sich besonders für modulare Automatisierungsprojekte, in denen Werte über standardisierte Schnittstellen ausgetauscht werden. Die interne Nutzung des bewährten `F_GE`‑Bausteins garantiert korrekte und performante Vergleichsoperationen.