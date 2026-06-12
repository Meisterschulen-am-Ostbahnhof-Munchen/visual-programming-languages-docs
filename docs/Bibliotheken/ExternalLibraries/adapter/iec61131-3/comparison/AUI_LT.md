# AUI_LT


![AUI_LT](./AUI_LT.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AUI_LT` realisiert einen Kleiner-als-Vergleich (`<`) zwischen zwei Eingangswerten. Er wird über Adapter-Schnittstellen angesprochen und eignet sich für den Einsatz in komponentenbasierten Automatisierungssystemen nach IEC 61131-3. Der Baustein führt den Vergleich asynchron durch und gibt das Ergebnis als booleschen Wert über einen Ausgangsadapter aus.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Bezeichnung | Beschreibung |
|------------|--------------|
| IN1.E1     | Ereignis am Socket-Adapter IN1; löst den Vergleich aus, sobald ein neuer Wert an IN1 anliegt. |
| IN2.E1     | Ereignis am Socket-Adapter IN2; löst den Vergleich aus, sobald ein neuer Wert an IN2 anliegt. |

### **Ereignis-Ausgänge**

| Bezeichnung | Beschreibung |
|------------|--------------|
| OUT.E1     | Ereignis am Plug-Adapter OUT; signalisiert, dass nach einem Vergleich ein gültiges Ergebnis an OUT.D1 anliegt. |

### **Daten-Eingänge**

| Bezeichnung | Beschreibung |
|------------|--------------|
| IN1.D1     | Erster Wert des Vergleichs (ANY_BIT-kompatibel). |
| IN2.D1     | Zweiter Wert des Vergleichs (ANY_BIT-kompatibel). |

### **Daten-Ausgänge**

| Bezeichnung | Beschreibung |
|------------|--------------|
| OUT.D1     | Ergebnis des Vergleichs: `true`, wenn IN1.D1 < IN2.D1; sonst `false`. |

### **Adapter**

| Bezeichnung | Typ               | Richtung | Beschreibung |
|------------|-------------------|----------|--------------|
| IN1        | AUI (unidirectional) | Socket   | Eingangsadapter für den ersten Wert und dessen Ereignis. |
| IN2        | AUI (unidirectional) | Socket   | Eingangsadapter für den zweiten Wert und dessen Ereignis. |
| OUT        | AX (unidirectional) | Plug     | Ausgangsadapter für das Vergleichsergebnis und das zugehörige Ereignis. |

## Funktionsweise

Der `AUI_LT`-Baustein ist als Composite-FB realisiert. Intern wird ein einzelner `F_LT`-Funktionsblock (aus der IEC 61131-3 Vergleichsbibliothek) verwendet.

- Die **Ereignis-Eingänge** `IN1.E1` und `IN2.E1` sind beide mit dem `REQ`-Eingang des internen `F_LT` verbunden. Sobald an einem der beiden Adapter ein Ereignis eintrifft, wird der Vergleich angestoßen.
- Die **Datenwerte** `IN1.D1` und `IN2.D1` werden direkt an die entsprechenden Eingänge `IN1` und `IN2` des `F_LT` weitergeleitet.
- Nach Abschluss der Berechnung signalisiert der `F_LT` über seinen Ausgang `CNF` das Ereignis `OUT.E1` und stellt das Vergleichsergebnis am Datenausgang `OUT.D1` bereit.

Der Vergleich erfolgt nach der Logik: **IN1.D1 < IN2.D1 ⇒ OUT.D1 = true**, andernfalls `false`.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation**: Alle Ein- und Ausgänge erfolgen über unidirektionale Adapter (Typen `AUI` und `AX`). Dies ermöglicht eine lose Kopplung und Wiederverwendung in verschiedenen Umgebungen.
- **Asynchrone Auslösung**: Da beide Ereigniseingänge auf den gleichen `REQ` des internen `F_LT` führen, kann der Vergleich durch ein Ereignis an **einem** der beiden Eingänge gestartet werden. Es ist nicht erforderlich, dass beide Ereignisse gleichzeitig eintreffen.
- **Typkompatibilität**: Der Baustein arbeitet mit beliebigen `ANY_BIT`-Datentypen (z. B. `BOOL`, `BYTE`, `WORD`, `DWORD`, `LWORD`), sofern die angeschlossenen Adapter dies unterstützen.
- **Keine Zustandsspeicherung**: Der FB ist rein kombinatorisch; er speichert keine historischen Werte.

## Zustandsübersicht

Da der `AUI_LT` keine explizite Zustandsmaschine besitzt, existiert lediglich ein **impliziter Zustand**:

| Zustand | Beschreibung |
|---------|--------------|
| **Bereit** | Wartet auf ein Ereignis an IN1.E1 oder IN2.E1. Nach Auslösung wird der Vergleich durchgeführt und das Ergebnis über OUT ausgegeben. Der FB kehrt sofort in den Bereit-Zustand zurück. |

## Anwendungsszenarien

- **Grenzwertüberwachung**: Prüfen, ob ein Messwert unter einem Schwellwert liegt, z. B. `Temperatur < Grenzwert`.
- **Steuerungslogik**: Bedingte Aktivierung von Ausgängen, z. B. Ventil öffnen, wenn `Druck < Sollwert`.
- **Interlock-Bedingungen**: Sicherheitsabfragen, bei denen ein Betrieb nur erlaubt ist, wenn eine Größe kleiner als eine andere ist.
- **Vergleichsketten**: Kombination mit anderen Vergleichsbausteinen (z. B. `AUI_EQ`, `AUI_GT`) zur Realisierung komplexer logischer Bedingungen.

## Vergleich mit ähnlichen Bausteinen

| Baustein    | Funktion              | Schnittstelle | Besonderheit |
|-------------|-----------------------|---------------|--------------|
| **AUI_LT**  | Kleiner als (`<`)     | Adapter (AUI, AX) | Asynchron, zwei separate Ereigniseingänge |
| **F_LT**    | Kleiner als (`<`)     | Standard-Ports (REQ/CNF, ANY_BIT) | Direkte Ereignis-/Datenports, kein Adapter |
| **AUI_EQ**  | Gleich (`=`)          | Adapter (AUI, AX) | Gleiche Struktur, anderer Vergleichsoperator |
| **AUI_GT**  | Größer als (`>`)      | Adapter (AUI, AX) | Gleiche Struktur, anderer Vergleichsoperator |

Der `AUI_LT` bietet durch die Adapter-Schnittstellen eine besonders flexible Integration in IEC 61131-3-konforme Systeme, während der interne `F_LT` die standardisierte Vergleichslogik bereitstellt.

## Fazit

Der `AUI_LT` ist ein kompakter und zuverlässiger Funktionsblock für Kleiner-als-Vergleiche in adapterbasierten Automatisierungsumgebungen. Seine asynchrone Ereignisverarbeitung und die lose Kopplung über Adapter machen ihn ideal für modulare Steuerungsanwendungen, bei denen einfache Bedingungen dezentral und ressourcenschonend ausgewertet werden müssen.