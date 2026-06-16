# AUI_FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE


![AUI_FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE](./AUI_FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock `AUI_FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE` dient der Umwandlung und Skalierung eines über einen AUI-Feldbusadapter eingehenden 16‑Bit‑Wertes in ein skalierbares Signal. Der Baustein spiegelt den Eingangswert auf den Ausgang, sofern das Gültigkeitssignal aktiv ist, und führt dabei eine zusammengesetzte Skalierung für das obere und untere Byte des Eingangswertes durch. Ein Offset kann nach der Skalierung addiert werden. Die Ausgabe erfolgt über einen unidirektionalen AR‑Adapter, während die Gültigkeit über einen AX‑Adapter signalisiert wird. Der Baustein ist insbesondere für industrielle Feldbusprotokolle konzipiert, bei denen Nutzdaten aus zwei getrennt skalierbaren Byte‑Bereichen bestehen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|-------------|
| INIT | EInit | Initialisierungsanforderung; versetzt den Baustein in einen definierten Startzustand. |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|-------------|
| INITO | EInit | Initialisierungsbestätigung; wird nach erfolgreicher Initialisierung gesendet. |

### **Daten-Eingänge**

| Variable | Typ | Initialwert | Beschreibung |
|----------|-----|-------------|-------------|
| SCALE_HIGH | REAL | 0.256 | Skalierungsfaktor für das obere Byte des eingehenden Wertes. |
| SCALE_LOW  | REAL | 0.001 | Skalierungsfaktor für das untere Byte des eingehenden Wertes. |
| OFFSET     | DINT | 0          | Ganzzahliger Offset, der nach der Skalierung addiert wird. |

### **Daten-Ausgänge**
Der Baustein besitzt keine separaten Datenausgänge als `VarDeclaration`. Die Ausgangsdaten werden über die Adapter `OUT` und `VALID` bereitgestellt.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|-------------|
| IN      | Socket   | adapter::types::unidirectional::AUI | Eingang für den zu verarbeitenden Feldbus‑Datenwert. |
| OUT     | Plug     | adapter::types::unidirectional::AR  | Ausgang des skalierten Werts (z. B. REAL oder DINT, abhängig vom internen Baustein). |
| VALID   | Plug     | adapter::types::unidirectional::AX  | Ausgangssignal: TRUE, wenn der aktuelle Ausgangswert gültig ist. |

## Funktionsweise
Der Baustein arbeitet als Composite‑Funktionsblock, der einen internen Baustein `FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE` in Kombination mit einem flankengesteuerten D‑Flipflop (`E_D_FF`) verwendet. Die Verarbeitung läuft wie folgt ab:

1. **Eingangsereignis**: Ein Ereignis am Ereigniseingang `IN.E1` des AUI‑Adapters triggert die Verarbeitung des momentanen Datenwerts `IN.D1`.
2. **Skalierung**: Der eingehende 16‑Bit‑Wert wird in ein oberes und ein unteres Byte aufgeteilt. Jedes Byte wird mit dem zugehörigen Skalierungsfaktor (`SCALE_HIGH`, `SCALE_LOW`) multipliziert. Das Ergebnis beider Skalierungen wird summiert und der `OFFSET` addiert. Der so berechnete Wert wird über den Datenausgang des internen Bausteins an `OUT.D1` weitergegeben.
3. **Gültigkeitssignal**: Parallel generiert der interne Baustein ein logisches Signal `VALID`, das anzeigt, ob der berechnete Wert gültig ist. Dieses Signal wird durch das D‑Flipflop mit dem Abschlussereignis `CNF` getaktet und an den `VALID.D1`‑Adapter weitergeleitet. Dadurch wird sichergestellt, dass das Gültigkeitssignal nur dann aktiv wird, wenn der Wert tatsächlich neu berechnet wurde.
4. **Ausgangsereignis**: Mit dem `CNF`‑Ereignis des internen Bausteins wird sowohl der Ausgangsadapter `OUT` (Ereignis `E1`) als auch der `VALID`‑Adapter (Ereignis `E1`) bedient.
5. **Initialisierung**: Das `INIT`‑Ereignis wird direkt an den internen Baustein weitergeleitet; die Initialisierungsbestätigung `INITO` wird entsprechend zurückgegeben.

## Technische Besonderheiten
- **Compound‑Skalierung**: Anders als einfache Skalierungsbausteine ermöglicht dieser FB eine separate Gewichtung der beiden Byte‑Hälften eines 16‑Bit‑Wertes. Dies ist nützlich, wenn ein Sensorwert aus zwei verschiedenen physikalischen Größen zusammengesetzt ist (z. B. ganze Zahl und Nachkommastelle).
- **Integrierte Gültigkeitslogik**: Durch das D‑Flipflop wird das `VALID`‑Signal flankengesteuert und nur bei tatsächlich neuen Berechnungen aktiviert. Dadurch werden unerwünschte Ausgaben bei fehlender Aktualisierung vermieden.
- **Initialisierungsdurchleitung**: Die INIT‑/INITO‑Ereignisse werden transparent durch den Composite‑Baustein gereicht, sodass der interne Skalierungsbaustein korrekt initialisiert werden kann.

## Zustandsübersicht
Der Baustein selbst besitzt keinen expliziten Zustandsautomaten auf Composite‑Ebene. Die Betriebsbereitschaft wird durch das `INIT`‑Ereignis hergestellt. Nach erfolgreicher Initialisierung wartet der Baustein auf eingehende Ereignisse am `IN`‑Adapter und verarbeitet diese zyklisch. Solange kein INIT‑Ereignis gesendet wurde, befindet sich der FB in einem undefinierten Zustand (keine Ausgabe, `VALID` inaktiv).

## Anwendungsszenarien
- **Feldbusschnittstellen**: Umwandlung von analogen Sensorwerten, die als 16‑Bit‑Wort mit getrennten Skalierungsfaktoren für Vor‑ und Nachkommaanteil übertragen werden (z. B. Temperatur‑/Druckwerte mit Nachkommastelle).
- **Messwertaufbereitung**: Skalierung von digitalen Eingangssignalen aus Feldbus‑Controllern, die Rohdaten in zwei Byte‑Bereichen liefern.
- **Signalvalidierung**: Einsatz in sicherheitsgerichteten Anwendungen, bei denen nur gültige und korrekt berechnete Werte an die nachfolgende Steuerung weitergegeben werden dürfen.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einfachen Skalierungsblöcken (z. B. `SCALE` oder `UINT_TO_REAL`) bietet dieser Baustein eine differenzierte Verarbeitung der beiden Byte‑Hälften. Er ist speziell für Datenformate ausgelegt, bei denen das obere und untere Byte unterschiedliche physikalische Einheiten oder Skalierungsbereiche repräsentieren. Alternative Bausteine müssten diese Logik manuell durch Aufteilung, separate Skalierung und anschließende Addition abbilden, was den Implementierungsaufwand erhöht.

## Fazit
Der `AUI_FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE` ist ein spezialisierter, aber flexibler Funktionsblock für die Aufbereitung von Feldbussignalen. Seine Fähigkeit, ein eingehendes 16‑Bit‑Wort mit zwei unterschiedlichen Skalierungsfaktoren zu verarbeiten und die Gültigkeit des Ausgangssignals zu steuern, macht ihn zu einem wertvollen Baustein in IEC‑61499‑basierten Automatisierungssystemen, insbesondere wenn es um die Integration von Geräten mit compoundierten Datenformaten geht.