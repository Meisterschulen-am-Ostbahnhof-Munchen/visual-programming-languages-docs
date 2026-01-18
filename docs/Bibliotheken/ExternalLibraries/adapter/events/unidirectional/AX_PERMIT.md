# AX_PERMIT (Unidirectional Adapter Permit)

```{index} single: AX_PERMIT (Unidirectional Adapter Permit)
```

## 🎧 Podcast

* [Der E_PERMIT-Baustein: Der "Türsteher" für Ereignisse in IEC 61499-Systemen entschlüsselt](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_PERMIT-Baustein-Der-Trsteher-fr-Ereignisse-in-IEC-61499-Systemen-entschlsselt-e3681m5)
* [Decoding E_PERMIT: The Unsung Hero of Industrial Automation's Safety and Reliability](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/Decoding-E_PERMIT-The-Unsung-Hero-of-Industrial-Automations-Safety-and-Reliability-e3681l1)
* [Code-Renovierung mit AX-Adaptern: Wie Eclipse 4diac™ durch Signal-Bündelung Komplexität besiegt](https://podcasters.spotify.com/pod/show/logibus/episodes/Code-Renovierung-mit-AX-Adaptern-Wie-Eclipse-4diac-durch-Signal-Bndelung-Komplexitt-besiegt-e3ahcd1)
* [Von 1400 Fehlern zum sauberen Code: Die Migration der „Getreidehacke“ auf Eclipse 4diac™ 3.0 und die Macht der AX-Adapter](https://podcasters.spotify.com/pod/show/logibus/episodes/Von-1400-Fehlern-zum-sauberen-Code-Die-Migration-der-Getreidehacke-auf-Eclipse-4diac-3-0-und-die-Macht-der-AX-Adapter-e3ahcko)

## 📺 Video

* [Gesteuerte Verbreitung eines Ereignisses E_PERMIT aus der IEC 61499 (Übung 94)](https://www.youtube.com/watch?v=ry5LTRd9H3M)
* [2025-11-04 20-15-06 LogiBUS® auf dem Weg zu Eclipse 4diac™ 3.0 - noch mehr Adapter (AX)](https://www.youtube.com/watch?v=RsY65VqTAMc)

## Einleitung
Der `AX_PERMIT` Funktionsblock ist eine adapterbasierte Variante des `E_PERMIT` Bausteins, implementiert als **Basic Function Block**. Er ermöglicht die bedingte Weitergabe eines Ereignisses, basierend auf dem booleschen Datenwert eines eingehenden `AX`-Adapters.

Der Baustein empfängt ein kombiniertes Ereignis- und Bool-Signal über einen `AX`-Adapter (genannt `PERMIT`). Das eingehende Ereignis wird nur dann an den Ausgang (`EO`) weitergeleitet, wenn der boolesche Datenwert des `PERMIT`-Adapters (`PERMIT.D1`) `TRUE` ist. Der Datenwert `PERMIT.D1` wird dabei **nicht** am Ausgang (`EO`) weitergereicht, sondern nur als Bedingung genutzt.

## Schnittstellenstruktur

### **Adapter (Socket)**
- **PERMIT**: Eingangsadapter vom Typ `AX` (Ereignis `E1` + Daten `D1`). Dieser Adapter steuert den Baustein.

### **Ereignis-Ausgänge**
- **EO**: Reiner Ereignis-Ausgang (Typ `Event`). Dieser Event wird ausgelöst, wenn die Bedingung erfüllt ist.

## Funktionsweise
1.  **Ereignisempfang**: Wenn am `PERMIT`-Socket ein Ereignis (`PERMIT.E1`) eintrifft, wird der zugehörige boolesche Datenwert (`PERMIT.D1`) als Bedingung geprüft.
2.  **Bedingte Weiterleitung**: Nur wenn `PERMIT.D1 = TRUE` ist, wird der Ereignis-Ausgang `EO` ausgelöst. Andernfalls wird das Ereignis blockiert.
3.  **Datendurchleitung**: Der boolesche Datenwert (`PERMIT.D1`) wird vom Baustein verwendet, aber **nicht** über den Ereignis-Ausgang `EO` weitergereicht.

## Technische Besonderheiten
✔ **Basic Function Block**: Direkte Implementierung der Logik.
✔ **Adapter-basiert**: Nutzt `AX`-Adapter als Eingang.
✔ **Permissive Logik**: Leitet Ereignisse bedingt weiter.
✔ **Keine Datenweitergabe am Ausgang**: Der Ausgang `EO` ist ein reiner Ereignis-Ausgang und enthält keine Daten (`With Var` ist nicht definiert).

## Anwendungsszenarien
- **Freigabeschaltung**: Ein nachfolgender Baustein soll nur dann getriggert werden, wenn eine Freigabe (`PERMIT.D1 = TRUE`) aktiv ist.
- **Konditionale Ereignissteuerung**: Steuerung des Ereignisflusses basierend auf einem externen booleschen Status, der über einen AX-Adapter kommt.