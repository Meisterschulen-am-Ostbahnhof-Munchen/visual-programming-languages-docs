# E_PERMIT

```{index} single: E_PERMIT
```
## 🎧 Podcast

* [Der E_PERMIT-Baustein: Der "Türsteher" für Ereignisse in IEC 61499-Systemen entschlüsselt](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_PERMIT-Baustein-Der-Trsteher-fr-Ereignisse-in-IEC-61499-Systemen-entschlsselt-e3681m5)
* [Decoding E_PERMIT: The Unsung Hero of Industrial Automation's Safety and Reliability](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/Decoding-E_PERMIT-The-Unsung-Hero-of-Industrial-Automations-Safety-and-Reliability-e3681l1)

## Einleitung
Der `E_PERMIT` (Event Permit) ist ein grundlegender Funktionsbaustein nach IEC 61499, der als steuerbares "Tor" für Ereignisse fungiert. Er lässt ein Eingangereignis nur dann zum Ausgang passieren, wenn eine explizite Freigabebedingung erfüllt ist.

![E_PERMIT](E_PERMIT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge:**
- **EI (Event Input)**: Das zu prüfende Eingangereignis.
    - **Verbundene Daten**: `PERMIT`

### **Ereignis-Ausgänge:**
- **EO (Event Output)**: Der Ereignisausgang, der nur ausgelöst wird, wenn die Freigabe erteilt wurde.

### **Daten-Eingänge:**
- **PERMIT**: Die Freigabebedingung (Datentyp: `BOOL`).

## Funktionsweise
1.  **Ereignisempfang**: Der Baustein wartet auf ein Ereignis am Eingang `EI`.
2.  **Prüfung der Freigabe**: Wenn das `EI`-Ereignis eintrifft, wird der Wert der Datenvariable `PERMIT` ausgewertet.
3.  **Bedingte Weiterleitung**:
    - **Wenn `PERMIT` = `TRUE` ist**: Das Ereignis wird durchgelassen und am Ausgang `EO` ausgegeben.
    - **Wenn `PERMIT` = `FALSE` ist**: Das Ereignis wird blockiert und es geschieht nichts. Der Ausgang `EO` wird nicht ausgelöst.

Der Baustein agiert somit als einfacher Wächter für den Ereignisfluss.

## Technische Besonderheiten
- **Ereignis-Tor**: Dient als grundlegendes "Gate" zur Steuerung von Ereignisströmen.
- **Zustandslos**: Der Baustein selbst hat keinen internen Speicher; seine Entscheidung basiert ausschließlich auf dem Wert von `PERMIT` im Moment des `EI`-Ereignisses.

## Anwendungsszenarien
- **Freigaben/Interlocks**: Ein Prozessschritt (`EI`) darf nur dann gestartet werden, wenn eine Sicherheitsfreigabe (`PERMIT`) vorliegt (z.B. Schutztür geschlossen).
- **Betriebsarten-Umschaltung**: Befehle von einer manuellen Steuerung (`EI`) werden nur dann weitergeleitet, wenn die Anlage im "Hand"-Modus ist (`PERMIT` = true).
- **Daten-Validierung**: Ein Ereignis, das die Weiterverarbeitung von Daten anstößt, wird nur ausgelöst, wenn eine vorherige Prüfung der Daten erfolgreich war (`PERMIT` = true).

## Vergleich mit ähnlichen Bausteinen
- **`E_SWITCH`**: Während `E_PERMIT` ein Ereignis entweder durchlässt oder blockiert (1-zu-1 oder 1-zu-0), leitet `E_SWITCH` ein Ereignis an einen von zwei verschiedenen Ausgängen weiter (1-zu-2). `E_PERMIT` ist ein Tor, `E_SWITCH` ist eine Weiche.




## Zugehörige Übungen

* [Uebung_009](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_009.md)
* [Uebung_080c](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_080c.md)
* [Uebung_094](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_094.md)

## Fazit
Der `E_PERMIT`-Baustein ist ein fundamentaler und weit verbreiteter Baustein zur Implementierung von Bedingungen und Freigaben in der ereignisgesteuerten Logik von IEC 61499. Seine Einfachheit und klare Funktion machen ihn zu einem unverzichtbaren Werkzeug für die Erstellung von sicheren und robusten Steuerungsabläufen.