### E_TRAIN

## Bild

![image](https://github.com/user-attachments/assets/5fe13f2e-9e23-49c6-ae8c-3faec87c42c4)


Zeigt eine Ereignisfolge 

CV N Ereignisse zur Periode DT, beginnend bei DT nach START

DT Time Periode zwischen Ereignissen

N UINT Anzahl der zu erzeugenden Ereignisse

![image](https://user-images.githubusercontent.com/113907658/227975285-56a17b67-0248-4336-8eef-829cf2d5d698.png)


Über Event Start wird das Ereignis gestartet und über Stopp angehalten.
Durch CV werden die aktuellen Ergebnisse gezählt und auf E0 das generierte Ergebnis
Time stellt die Zeit da in welchen abständen das Event auftreten soll
Unit wie viel Event bereit durchgeführt wurden










![E_TRAIN](https://user-images.githubusercontent.com/116869307/214142742-8ce9523e-eb2b-416c-afe8-109fb601dd20.png)




## Beschreibung


Der Baustein **E_TRAIN** ist ein Funktionsbaustein (FB) nach der Norm **IEC 61499**, der verwendet wird, um eine endliche Folge von Ereignissen zu generieren, die durch eine bestimmte Zeitdauer (**DT**) voneinander getrennt sind. Dieser Baustein ist nützlich in Steuerungsanwendungen, bei denen eine Reihe von zeitlich getrennten Ereignissen benötigt wird, z. B. in Prozessen, die periodische Aktionen erfordern.

### Beschreibung des Bausteins E_TRAIN:

#### **Allgemeine Funktion:**
- Der Baustein **E_TRAIN** generiert eine endliche Anzahl von Ereignissen (**EO**), die durch eine vorgegebene Zeitdauer (**DT**) voneinander getrennt sind.
- Die Anzahl der zu generierenden Ereignisse wird durch den Eingang **N** festgelegt.
- Jedes generierte Ereignis (**EO**) enthält einen Zählerwert (**CV**), der den Index des aktuellen Ereignisses angibt (0 bis N-1).
- Der Baustein kann durch das **START**-Ereignis gestartet und durch das **STOP**-Ereignis gestoppt werden.

#### **Schnittstellen (Interface):**

1. **Eingangsereignisse (Event Inputs):**
   - **START:** Dieses Ereignis startet die Generierung der Ereignisfolge. Es ist mit den Eingangsvariablen **DT** (Zeitabstand zwischen den Ereignissen) und **N** (Anzahl der zu generierenden Ereignisse) verknüpft.
   - **STOP:** Dieses Ereignis stoppt die Generierung der Ereignisse. Wenn **STOP** ausgelöst wird, wird die Ereignisgenerierung sofort beendet, unabhängig davon, wie viele Ereignisse bereits generiert wurden.

2. **Ausgangsereignisse (Event Outputs):**
   - **EO (Generated Events):** Dieses Ereignis wird jedes Mal ausgelöst, wenn ein neues Ereignis generiert wird. Es ist mit der Ausgangsvariablen **CV** (Zählerwert) verknüpft, der den Index des aktuellen Ereignisses angibt.

3. **Eingangsvariablen (Input Variables):**
   - **DT (TIME):** Die Zeitdauer, die zwischen den generierten Ereignissen vergehen soll.
   - **N (UINT):** Die Anzahl der Ereignisse, die generiert werden sollen.

4. **Ausgangsvariablen (Output Variables):**
   - **CV (UINT):** Der Zählerwert, der den Index des aktuellen Ereignisses angibt (0 bis N-1).

#### **Internes Netzwerk (FBNetwork):**
Der Baustein **E_TRAIN** verwendet intern mehrere andere Funktionsbausteine, um die Ereignisgenerierung zu realisieren:

1. **E_CTU (Counter):**
   - Dieser Baustein zählt die Anzahl der generierten Ereignisse. Er wird verwendet, um sicherzustellen, dass nur die angegebene Anzahl von Ereignissen (**N**) generiert wird.
   - Der Zählerwert (**CV**) wird an den Ausgang **CV** des **E_TRAIN**-Bausteins weitergeleitet.

2. **E_SWITCH (Switch):**
   - Dieser Baustein wird verwendet, um den Fluss der Ereignisse zu steuern. Er ermöglicht es, die Ereignisgenerierung zu starten und zu stoppen, basierend auf dem Zustand des Zählers (**E_CTU**).

3. **E_DELAY (Delay):**
   - Dieser Baustein sorgt dafür, dass die Ereignisse mit dem angegebenen Zeitabstand (**DT**) generiert werden. Er wird verwendet, um die Zeit zwischen den Ereignissen zu steuern.

#### **Verhalten:**
- Wenn das **START**-Ereignis ausgelöst wird, beginnt der Baustein mit der Generierung der Ereignisse.
- Jedes Ereignis wird durch das **EO**-Ereignis signalisiert, und der Zählerwert **CV** wird entsprechend erhöht.
- Die Ereignisse werden im Abstand von **DT** generiert, bis die angegebene Anzahl von Ereignissen (**N**) erreicht ist.
- Wenn das **STOP**-Ereignis ausgelöst wird, wird die Ereignisgenerierung sofort beendet, unabhängig davon, wie viele Ereignisse bereits generiert wurden.

#### **Anwendungsbeispiele:**
- **Periodische Steuerung:** Der Baustein kann verwendet werden, um periodische Aktionen in einer Steuerung zu realisieren, z. B. das periodische Einschalten einer Pumpe oder eines Motors.
- **Testsequenzen:** In Testumgebungen kann der Baustein verwendet werden, um eine Reihe von Testereignissen zu generieren, die in regelmäßigen Abständen ausgelöst werden.
- **Blinklichtsteuerung:** Der Baustein kann verwendet werden, um eine Reihe von Blinklichtsignalen zu generieren, die in bestimmten Zeitabständen aufleuchten.

#### **Versionierung:**
- **Version 1.0:** Ursprüngliche Version des Bausteins, erstellt von Alois Zoitl am 22.09.2017.
- **Version 1.1:** Eine Fehlerbehebung wurde durchgeführt, und der Baustein wurde von Franz Höpfinger am 15.02.2025 aktualisiert.

### Zusammenfassung:
Der **E_TRAIN**-Baustein ist ein nützliches Werkzeug in der IEC 61499-basierten Steuerungstechnik, um eine endliche Folge von zeitlich getrennten Ereignissen zu generieren. Durch seine einfache Schnittstelle und das klare Verhalten ist er leicht in verschiedene Steuerungsanwendungen integrierbar. Die interne Verwendung von **E_CTU**, **E_SWITCH** und **E_DELAY** sorgt für eine zuverlässige und präzise Ereignisgenerierung.





























