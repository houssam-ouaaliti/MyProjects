<div class="mt-4 border-t pt-4">
    @if($successMessage)
        <div class="bg-green-100 text-green-700 p-2 rounded text-sm font-bold">
            {{ $successMessage }}
        </div>
    @else
        <form wire:submit.prevent="save" class="space-y-3">
            <div>
                <label class="text-xs font-semibold text-gray-500 block mb-1">Arrivée</label>
                <input 
                    type="date" 
                    wire:model="start_date" 
                    class="block w-full text-sm border border-gray-300 rounded-md shadow-sm focus:border-primary focus:ring-primary px-3 py-2">
                @error('start_date') 
                    <span class="text-red-500 text-xs mt-1 block">{{ $message }}</span> 
                @enderror
            </div>
            
            <div>
                <label class="text-xs font-semibold text-gray-500 block mb-1">Départ</label>
                <input 
                    type="date" 
                    wire:model="end_date" 
                    class="block w-full text-sm border border-gray-300 rounded-md shadow-sm focus:border-primary focus:ring-primary px-3 py-2">
                @error('end_date') 
                    <span class="text-red-500 text-xs mt-1 block">{{ $message }}</span> 
                @enderror
            </div>

            <button 
                type="submit" 
                class="w-full bg-secondary text-white px-4 py-2 rounded-md hover:bg-purple-600 transition text-sm font-bold mt-3">
                CONFIRMER LA RÉSERVATION
            </button>
        </form>
    @endif
</div>