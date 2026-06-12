# ADI_TO_AB


![ADI_TO_AB](./ADI_TO_AB.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ADI_TO_AB` dient als Komposit-Baustein zur Umwandlung eines 32‑Bit‑Integer‑Wertes (DINT) in einen Byte‑Wert (BYTE). Er kapselt die Konvertierung zwischen zwei unidirektionalen Adaptern: dem **ADI‑Adapter** (Eingang) und dem **AB‑Adapter** (Ausgang). Der Baustein wird eingesetzt, um Daten von einem DINT‑Adapter auf einen BYTE‑Adapter zu übertragen, ohne dass der Anwender die eigentliche Konvertierungslogik selbst implementieren muss.

## Schnittstellenstruktur

### **Ereignis‑Eingänge**

Der Baustein besitzt keine direkten Ereignis‑Eingänge. Der Ereignis‑Empfang erfolgt über den **Socket‑Adapter ADI_IN**:

| Adapter‑Port | Typ        | Beschreibung                          |
|--------------|------------|---------------------------------------|
| ADI_IN.E1    | Ereignis   | Startet die Konvertierung am Eingang. |

### **Ereignis‑Ausgänge**

Auch die Ereignis‑Ausgabe erfolgt ausschließlich über den **Plug‑Adapter AB_OUT**:

| Adapter‑Port | Typ        | Beschreibung                         |
|--------------|------------|--------------------------------------|
| AB_OUT.E1    | Ereignis   | Signalisiert, dass der Wert konvertiert und am Ausgang bereitsteht. |

### **Daten‑Eingänge**

Die Daten werden über den ADI_IN‑Adapter bereitgestellt:

| Adapter‑Port | Typ  | Beschreibung                     |
|--------------|------|----------------------------------|
| ADI_IN.D1    | DINT | 32‑Bit‑Integer‑Eingangswert.     |

### **Daten‑Ausgänge**

Die konvertierten Daten werden über den AB_OUT‑Adapter ausgegeben:

| Adapter‑Port | Typ  | Beschreibung               |
|--------------|------|----------------------------|
| AB_OUT.D1    | BYTE | 8‑Bit‑Byte‑Ausgangswert.   |

### **Adapter**

| Name    | Richtung | Typ des Adapters                         | Beschreibung                   |
|---------|----------|------------------------------------------|--------------------------------|
| ADI_IN  | Socket   | `adapter::types::unidirectional::ADI`    | DINT‑Adapter als Eingang.      |
| AB_OUT  | Plug     | `adapter::types::unidirectional::AB`     | BYTE‑Adapter als Ausgang.      |

## Funktionsweise

Intern verwendet der Baustein den vordefinierten IEC‑61131‑3‑Funktionsbaustein `F_DINT_TO_BYTE`, um die eigentliche Datentypkonvertierung durchzuführen. Die Ereignis‑ und Datenflüsse sind wie folgt:

1. Ein Ereignis am **ADI_IN.E1** triggert die Konvertierung.
2. Der Datenwert von **ADI_IN.D1** wird an den Eingang `IN` des internen `F_DINT_TO_BYTE`‑Bausteins weitergeleitet.
3. Nach Abschluss der Konvertierung erzeugt der interne Baustein das Ereignis **CNF**.
4. Dieses Ereignis wird als **AB_OUT.E1** nach außen gegeben.
5. Gleichzeitig steht der konvertierte Wert am Ausgang `OUT` des internen Bausteins bereit und wird über **AB_OUT.D1** ausgegeben.

Die gesamte Logik ist in einem Composite‑FB gekapselt, sodass der Anwender nur die Adapter verbinden muss.

## Technische Besonderheiten

- **Composite‑FB**: Der Baustein besteht aus einem internen Netzwerk und besitzt keine eigene Zustandsmaschine (ECC). Er führt die Konvertierung streng ereignisgesteuert aus.
- **Verwendung von IEC‑61131‑3‑Standard‑Bausteinen**: Die Konvertierung erfolgt mit dem normierten Baustein `F_DINT_TO_BYTE`, was Portabilität und Einhaltung von Industriestandards gewährleistet.
- **Adapter‑basierte Ein‑/Ausgabe**: Alle Daten und Ereignisse werden über Adapter – und nicht über einzelne Ports – geführt. Dies vereinfacht die Anbindung an gleichartige Adapter‑Schnittstellen in der 4diac‑Umgebung.

## Zustandsübersicht

Da es sich um einen Composite‑FB ohne eigene Zustandsmaschine handelt, existieren keine expliziten Zustände. Der Baustein reagiert auf das eingehende Ereignis, konvertiert den Wert und gibt das Ergebnis aus. Nach der Ausgabe ist er sofort bereit für eine neue Konvertierung.

## Anwendungsszenarien

- **Datenprotokoll‑Anpassung**: Wenn ein Sensor oder eine Steuerung DINT‑Werte liefert, das angeschlossene Gerät oder der Kommunikationskanal jedoch BYTE‑Werte erwartet.
- **Adapter‑Vermittlung**: In einer modularen Architektur, die den Austausch von Adaptern mit unterschiedlichen Datentypen ermöglicht, ohne die Verbindungslogik jedes Mal neu schreiben zu müssen.
- **Schnittstellen‑Kopplung**: Zwischen Komponenten, die unidirektionale Adapter nutzen, z. B. in einer Pipeline‑Struktur.

## Vergleich mit ähnlichen Bausteinen

Es gibt zahlreiche Konvertierungsbausteine für direkte Datentypumwandlungen (z. B. `F_DINT_TO_INT`, `F_DINT_TO_WORD`). Der `ADI_TO_AB` unterscheidet sich dadurch, dass er keine einzelnen Daten‑ und Ereignisports, sondern vollständige Adapter verwendet. Dadurch wird die Kapselung verbessert und die Wiederverwendbarkeit erhöht. Ein ähnliches Konzept existiert für andere Datentyp‑Paare (z. B. `ADI_TO_AC` für DINT nach CHAR), die der gleichen Entwurfslogik folgen.

## Fazit

Der Funktionsblock `ADI_TO_AB` bietet eine sauber gekapselte, adaptergestützte Konvertierung von DINT‑ nach BYTE‑Werten. Er nutzt Standard‑IEC‑Bausteine und Ereignissteuerung, sodass er sich nahtlos in 4diac‑Projekte integrieren lässt. Durch die Adapter‑Schnittstellen ist er besonders für modulare und wiederverwendbare Steuerungsanwendungen geeignet.