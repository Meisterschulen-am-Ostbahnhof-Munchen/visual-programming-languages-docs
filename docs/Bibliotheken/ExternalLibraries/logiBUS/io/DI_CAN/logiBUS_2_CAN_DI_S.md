# logiBUS_2_CAN_DI_S

```{index} single: logiBUS_2_CAN_DI_S
```

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `logiBUS_2_CAN_DI_S` ist ein strukturierter Datentyp (Struct), der zur Konfiguration eines digitalen Eingangs (DI) für ein logiBUS-CAN-System dient. Er definiert die grundlegenden Parameter, die benötigt werden, um einen physischen Eingangspin auf einem logiBUS-CAN-Modul zu adressieren und zu nutzen. Dieser Datentyp dient typischerweise als Eingabe für übergeordnete Funktionsbausteine, die die eigentliche Kommunikation über das CAN-Protokoll abwickeln.

## Schnittstellenstruktur
Dies ist ein strukturierter Datentyp (STRUCT) und besitzt daher keine Ereignis- oder Adapterschnittstellen. Seine Struktur besteht aus einem einzelnen Datenelement.

### **Daten-Eingänge**
Da es sich um einen Datentyp handelt, werden diese Elemente innerhalb eines übergeordneten Funktionsbausteins als Eingangsdaten verwendet.

| Name | Datentyp | Initialwert | Kommentar |
|---|---|---|---|
| `Pin` | `USINT` (Unsigned Short Integer) | 255 | Definiert die Nummer des physischen Eingangspins am logiBUS-CAN-Modul. |

### **Daten-Ausgänge**
*(Nicht zutreffend für einen strukturierten Datentyp)*

### **Ereignis-Eingänge**
*(Nicht zutreffend für einen strukturierten Datentyp)*

### **Ereignis-Ausgänge**
*(Nicht zutreffend für einen strukturierten Datentyp)*

### **Adapter**
*(Nicht zutreffend für einen strukturierten Datentyp)*

## Funktionsweise
Der Datentyp `logiBUS_2_CAN_DI_S` fungiert als Konfigurationscontainer. Der enthaltene Wert `Pin` spezifiziert, welcher konkrete digitale Eingang eines logiBUS-CAN-I/O-Moduls angesprochen werden soll. Der Initialwert `255` stellt einen typischen ungültigen oder nicht konfigurierten Zustand dar, der eine explizite Zuweisung einer gültigen Pinnummer durch den Anwender erfordert. Ein übergeordneter Funktionsbaustein (z.B. ein Treiber-FB) liest diese Struktur aus und verwendet die `Pin`-Information, um die korrekten CAN-Telegramme zu generieren oder zu interpretieren, die den Zustand (Ein/Aus) des jeweiligen Eingangs abfragen.

## Technische Besonderheiten
*   **Datentyp `USINT`:** Die Verwendung eines `USINT` (0 bis 255) für den Pin legt nahe, dass die logiBUS-Hardware theoretisch bis zu 256 digitale Eingänge pro Konfigurationsstruktur adressieren kann. Der Wert 255 ist als Standard-Initialwert reserviert.
*   **Initialwert 255:** Dieser Wert dient als Kennzeichnung für eine nicht aktive oder nicht definierte Konfiguration. Er sollte in der Anwendung durch eine gültige Pinnummer ersetzt werden.
*   **Packagename:** Der Datentyp ist im Package `logiBUS::io::DI_CAN` organisiert, was seine Zugehörigkeit zur logiBUS-CAN-Eingangskommunikation klar kennzeichnet.

## Zustandsübersicht
*(Nicht zutreffend für einen strukturierten Datentyp. Der "Zustand" ist lediglich der gespeicherte Wert der `Pin`-Variable.)*

## Anwendungsszenarien
Dieser Strukturtyp wird in Szenarien eingesetzt, bei denen digitale Signale (z.B. Schalter, Endschalter, Sensorkontakte) über ein CAN-basiertes logiBUS-Netzwerk in eine Steuerung (z.B. eine IEC 61499-basierte Applikation in 4diac) eingelesen werden sollen. Typische Anwendungen sind:
*   Maschinensteuerungen mit dezentraler, CAN-vernetzter Sensorik.
*   Mobile Anwendungen (Fahrzeuge, Roboter) mit robustem Bussystem.
*   Anlagen, bei denen digitale Eingangssignale über größere Entfernungen verteilt sind.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu direkten I/O-Funktionsbausteinen (wie z.B. `E_SR` oder `E_D_FF`), die logische Zustände verarbeiten, ist `logiBUS_2_CAN_DI_S` ein reiner **Konfigurationsdatentyp**. Er ist vergleichbar mit anderen strukturierten Hardware-Konfigurationstypen in 4diac (z.B. für serielle Schnittstellen oder andere Feldbusse), die Parameter für die Hardware-Anbindung kapseln. Sein Gegenstück für digitale Ausgänge wäre ein entsprechender Struct-Typ (z.B. `logiBUS_2_CAN_DO_S`).

## Fazit
Der `logiBUS_2_CAN_DI_S` Datentyp ist ein essentielles und schlankes Konfigurationselement für die Anbindung digitaler Eingänge an ein CAN-basiertes logiBUS-System innerhalb der 4diac IDE. Durch die Kapselung der Pinnummer in eine strukturierte Variable ermöglicht er eine klare, typgesicherte und wartbare Konfiguration der Hardware-Schnittstelle in übergeordneten Steuerungsalgorithmen. Die Verwendung eines eindeutigen Initialwerts hilft, Fehlkonfigurationen frühzeitig zu erkennen.