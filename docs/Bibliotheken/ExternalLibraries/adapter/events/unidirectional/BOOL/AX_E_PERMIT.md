# AX_E_PERMIT


![AX_E_PERMIT](./AX_E_PERMIT.svg)

* * * * * * * * * *
## Einleitung

Der Baustein **AX_E_PERMIT** realisiert eine bedingte Ereignisweitergabe (permissive propagation). Ein eingehendes Ereignis wird nur dann an den Ausgang weitergeleitet, wenn ein über einen Adapter bereitgestelltes Freigabesignal (Permit) den Wert `TRUE` besitzt. Der Baustein dient als Gate, das die Verarbeitungskette in Abhängigkeit von externen Bedingungen unterbrechen oder freigeben kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar      |
|------|-------|----------------|
| EI   | Event | Ereigniseingang |

### **Ereignis-Ausgänge**

| Name | Typ   | Kommentar       |
|------|-------|-----------------|
| EO   | Event | Ereignisausgang |

### **Daten-Eingänge**
Der Baustein besitzt keine eigenen Dateneingänge. Das Freigabesignal wird über einen Adapter bereitgestellt.

### **Daten-Ausgänge**
Der Baustein besitzt keine Datenausgänge.

### **Adapter**

| Rolle   | Name   | Typ                                    | Kommentar                     |
|---------|--------|----------------------------------------|-------------------------------|
| Socket  | PERMIT | `adapter::types::unidirectional::AX`   | Liefert das Freigabesignal (D1) |

Der Adapter ist unidirektional ausgelegt und stellt einen booleschen Wert (`D1`) zur Verfügung, der das Verhalten des Ereignisgates steuert.

## Funktionsweise

Der Baustein enthält intern einen Standard-Funktionsblock `E_PERMIT` aus der IEC-61499-Bibliothek. Das eingehende Ereignis `EI` wird direkt an den internen `E_PERMIT`-Eingang weitergeleitet. Dessen Ausgang `EO` ist nur dann aktiv, wenn der zugehörige Freigabeeingang (`PERMIT` des internen Blocks) den Wert `TRUE` annimmt. Dieses Freigabesignal wird aus dem Adapter `PERMIT` über die Verbindung `PERMIT.D1` gespeist.

Somit gilt:
- **Permit = TRUE:** Das Ereignis `EI` wird unverzögert an `EO` weitergegeben.
- **Permit = FALSE:** Das Ereignis wird unterdrückt; `EO` bleibt inaktiv.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle:** Das Freigabesignal wird nicht als klassischer Dateneingang, sondern über einen Adapter (`AX`, unidirektional) bereitgestellt. Dies ermöglicht eine modulare Kopplung und Wiederverwendung der Freigabelogik.
- **Keine Datenweiterleitung:** Der Baustein gibt selbst keine Daten aus. Er dient ausschließlich der Steuerung des Ereignisflusses.
- **Unidirektionaler Adapter:** Der Adapter liefert nur einen Datenwert (D1) zum Baustein; eine Rückkopplung ist nicht vorgesehen.
- **Verwendung eines Standardbausteins:** Intern wird der bewährte `E_PERMIT`-Block eingesetzt, der die eigentliche Freigabelogik implementiert.

## Zustandsübersicht

Der Baustein selbst besitzt keine sichtbaren Zustände. Das interne Verhalten wird durch den `E_PERMIT`-Block bestimmt, der im Wesentlichen eine passive Warteschleife darstellt:

- **Warten auf Ereignis:** Der Block wartet auf ein Ereignis am Eingang `EI`.
- **Prüfung des Permits:** Bei Eintreffen eines Ereignisses wird der Zustand des Freigabesignals ausgewertet.
- **Weiterleitung:** Nur wenn `PERMIT = TRUE` erfolgt die Ausgabe des Ereignisses an `EO`.

Eine explizite Zustandsmaschine ist nicht vorhanden; der Baustein arbeitet rein kombinatorisch auf Ereignisebene.

## Anwendungsszenarien

- **Sicherheitsverriegelung:** Ein Ereignis (z. B. Start einer Maschine) wird nur dann weitergeleitet, wenn ein externer Sicherheitskreis ein Freigabesignal liefert.
- **Bedingte Verarbeitung:** In einer Produktionssteuerung kann der Datenfluss von Sensoren nur bei aktiviertem Betriebsmodus an die übergeordnete Steuerung gesendet werden.
- **Test- und Simulationsumgebungen:** Ein Ereignis kann über ein manuelles Freigabesignal gezielt ein- oder ausgeblendet werden, um bestimmte Szenarien zu testen.
- **Ressourcenschonung:** In einer komplexen Automatisierungsanlage können nicht benötigte Ereignisse durch Deaktivieren des Permits unterdrückt werden, um die Buslast zu reduzieren.

## Vergleich mit ähnlichen Bausteinen

| Baustein          | Besonderheit                                                                 |
|-------------------|------------------------------------------------------------------------------|
| **E_PERMIT**      | Standardblock mit direktem booleschem Eingang. Kein Adapter.                 |
| **AX_E_PERMIT**   | Gleiche Logik, aber das Freigabesignal wird über einen unidirektionalen Adapter bereitgestellt, was die Kopplung über Subsysteme erleichtert. |
| **E_SR** (Set-Reset) | Ereignisbasierte Zustandsspeicherung; nicht direkt als Gate geeignet.        |
| **E_MUX**         | Ereignisweiche, die abhängig von einem Dateneingang zwischen zwei Ausgängen umschaltet – keine reine Sperrfunktion. |

Der Vorteil von `AX_E_PERMIT` liegt in der sauberen Trennung der Freigabelogik durch einen Adapter, was die Wiederverwendung von Steuerungsmodulen fördert.

## Fazit

Der Funktionsblock `AX_E_PERMIT` stellt eine flexible und modulare Lösung zur bedingten Ereignisweitergabe dar. Durch die Verwendung eines Adapters für das Freigabesignal wird die Schnittstelle klar definiert und kann über Hierarchiegrenzen hinweg eingesetzt werden. Der Baustein eignet sich besonders für sicherheitskritische oder konfigurierbare Steuerungsanwendungen, bei denen die Ereignisverarbeitung von externen Bedingungen abhängt.